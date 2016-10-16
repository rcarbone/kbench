/*** original authoring: Lightness1024!  ***/
/*** Copyright V.Oddou 08/2014           ***/
/*** lightness1024 -at- free -dot- fr    ***/

/*** licensing:

	- zlib (http://zlib.net/zlib_license.html)

		   This software is provided 'as-is', without any express or implied
		   warranty.  In no event will the authors be held liable for any damages
		   arising from the use of this software.

		   Permission is granted to anyone to use this software for any purpose,
		   including commercial applications, and to alter it and redistribute it
		   freely, subject to the following restrictions:

		   1. The origin of this software must not be misrepresented; you must not
		   claim that you wrote the original software. If you use this software
		   in a product, an acknowledgment in the product documentation would be
		   appreciated but is not required.
		   2. Altered source versions must be plainly marked as such, and must not be
		   misrepresented as being the original software.
		   3. This notice may not be removed or altered from any source distribution.

my word:
	  You can use and keep this code private to your organisation (closed source).
	  Without the need to mention this disclaimer in the distributed binary form of your product.
***/



// the behavior of this map is very largely based on C++11 unordered_map
// http://www.cplusplus.com/reference/unordered_map/unordered_map/

// it works with standard C++11 hashers as default (std::hash)
// requirements:
// any type used as key must have a hasher, and operator == (or an std::equal_to overload, or you can pass a custom equal-er)
// types used as values must be copiables (for buffer migration when extending)

// tested compilers:
//  MS VS 2013 & VS 2015
//  gcc 4.8 & gcc 4.9
//  clang 3.5 & 3.6

// no issues reported by valgrind

// terminology:
//
//  - OAHM : open address hash map
//
//  - open address : fact that the memory used to store your content is one straight flat buffer,
//                   and hashes are (almost) direct indices in it.
//
//  - linear probing : the strategy used by this hash map to resolve conflicts.
//
//  - bucket : a word chosen by linked-list based hash maps (LLHM e.g. std::unordered).
//             for a LLHM, a bucket is the host of the locality for one hash (i.e. all pairs of the same hash goes into one bucket).
//             therefore for a LLHM a bucket is a linked list.
//             (locality = by reference to local_iterator)
//             in this OAHM, a bucket is just ONE record and does not represent a hash family.
//             therefore in our case, a bucket is a `pair<k, v>`
//             hash families can get scattered over the memory zone and are found/placed using linear probing.
//
//  - load factor : the load factor is the contenance versus the reserved zone. this MUST be kept under 0.8
//
//  - delete contamination : when buckets get deleted, if some bucket exists right next to it, it marks itself as "deleted".
//                           this is to keep the linear-probing link working, marking it as "empty" would break the link
//                           with subsequent data, if any was placed after collision probing.
//                           unfortunately, this flag dirties the map space as deletion count increase,
//                           and searches will get slower.

// benchmark executed on core i5, linux, clang 3.6 -O3
// == 50k random finds among 32k contenance ==
// *openaddr HM: 	0.808362 ms
// std unordered: 	0.714579 ms
// std map: 		6.90065 ms


#ifndef HASHMAP_SERHUM_INCLUDEGUARD_L1024_82014
#define HASHMAP_SERHUM_INCLUDEGUARD_L1024_82014 1

#include <exception>
#include <new>
#include <tuple>
#include <vector>
#include <type_traits>
#include <cstddef>
#include <cstdint>
#include "pool.hpp"

#ifndef _countof
# define _countof(a) (sizeof(a) / sizeof(a[0]))
# define do_undef_countof_at_file_end
#endif

#ifdef _DEBUG
# define DBG_NLY(x) x
#else
# define DBG_NLY(x)
#endif

namespace container
{
	enum class buckstate : uint8_t { empty, occupied, deleted };

	struct buckets_state
	{
		void resize(size_t n)
		{
			occupancy.resize(n * 2);
		}

		bool is_all_false()
		{
			return std::find(occupancy.begin(), occupancy.end(), true) == occupancy.end();
		}

		buckstate get_at(size_t i) const
		{
			uint8_t lsb = occupancy[i * 2] ? 1 : 0;
			uint8_t msb = occupancy[i * 2 + 1] ? 1 : 0;
			uint8_t ibs = lsb | (msb << 1);
			_ASSERT(ibs <= 2);  // 3 is impossible.
			return buckstate(ibs);
		}

		void set_at(size_t i, buckstate bs)
		{
			uint8_t ibs = uint8_t(bs);
			_ASSERT(ibs <= 2);
			uint8_t lsb = ibs & 1;
			uint8_t msb = (ibs >> 1) & 1;
			occupancy[i * 2] = lsb != 0;
			occupancy[i * 2 + 1] = msb != 0;
		}

		size_t size() const { return occupancy.size() / 2; }

		void swap(buckets_state& rhs)
		{
			occupancy.swap(rhs.occupancy);
		}
	private:
		std::vector< bool > occupancy;  // store state (3 states) on 2 adjacent bits.
	};

	template< typename MapValueType >
	struct map_buckets
	{
		typedef MapValueType	value_type;

		map_buckets() = default;
		map_buckets(map_buckets const&) = delete;
		map_buckets(map_buckets&&) = delete;

		~map_buckets()
		{
			size_t i = 0;
			size_t lim = array.size();
			for ( ; i != lim; ++i)
			{
				if (occup.get_at(i) == buckstate::occupied)
					array[i].~value_type();
			}
		}

		buckets_state		occup;
		pool< value_type >	array;

		void resize(size_t n)
		{
			_ASSERT(array.size() == 0);  // cannot really resize. just set from 0.
			array.resize(n);
			occup.resize(n);
		}

		bool all_occupancy_is_empty()
		{
			return occup.is_all_false();
		}

		void swap(map_buckets& r)
		{
			occup.swap(r.occup);
			array.swap(r.array);
		}
	};

	//============================================================================
	// class hash_map<..>::iterator
	//============================================================================
	template< typename ObservedPairType, typename SourcePairType >
	class hash_map_iterator
	{
	public:
		typedef ObservedPairType pair_type;
		typedef typename pair_type::first_type	 key_t;
		typedef typename pair_type::second_type	 mapped_t;

		typedef ptrdiff_t difference_type;
		typedef pair_type value_type;
		typedef pair_type* pointer;
		typedef pair_type& reference;
		typedef std::bidirectional_iterator_tag iterator_category;

		static_assert(std::is_same< typename std::remove_const<key_t>::type,
									typename std::remove_const< typename SourcePairType::first_type >::type >::value,
					  "the both template arguments must have the same type, except qualification");

		static_assert(std::is_same< typename std::remove_const<mapped_t>::type,
									typename std::remove_const< typename SourcePairType::second_type >::type >::value,
					  "the both template arguments must have the same type, except qualification");

		hash_map_iterator();
		hash_map_iterator(map_buckets<SourcePairType>* buckets);
		hash_map_iterator(map_buckets<SourcePairType>* buckets, size_t current_offset);
		template< typename Obs2T >
		hash_map_iterator(hash_map_iterator< Obs2T, SourcePairType> const& copyfrom);

		pair_type*			operator-> () const;
		pair_type&			operator*  () const;
		hash_map_iterator&	operator++ ();  // prefix
		hash_map_iterator	operator++ (int);  // postfix
		template< typename PairT, typename SRCPairT >
		bool				operator== (hash_map_iterator<PairT, SRCPairT> const& rhs) const;
		template< typename PairT, typename SRCPairT >
		bool				operator!= (hash_map_iterator<PairT, SRCPairT> const& rhs) const;
		hash_map_iterator&	operator = (hash_map_iterator const& rhs);

		template< typename Ob, typename NCPT >
		friend class hash_map_iterator;
	private:
		pair_type* current;
		map_buckets<SourcePairType>* buckets_ref;
	};

#define ITER_TPL_DECL template< typename ObservedPairType, typename SourcePairType >
#define ITER_DECL hash_map_iterator<ObservedPairType, SourcePairType>

	// default construction -> just set to null.
	ITER_TPL_DECL
	ITER_DECL::hash_map_iterator()
			: current(nullptr),
			  buckets_ref(nullptr)
	{}

	// construction from a hashmap -> gives the information about the bucket we will iterate.
	ITER_TPL_DECL
	ITER_DECL::hash_map_iterator(map_buckets<SourcePairType>* buckets)
			: current(nullptr),
			  buckets_ref(buckets)
	{}

	ITER_TPL_DECL
	ITER_DECL::hash_map_iterator(map_buckets<SourcePairType>* buckets, size_t current_offset)
		: buckets_ref(buckets)
	{
		current = buckets->array.size() == 0 ? nullptr : (pair_type*)&buckets->array[0] + current_offset;
	}

	// copy construction. it should be able to copy from const_iterator (therefore template)
	ITER_TPL_DECL
	template< typename Obs2T >
	ITER_DECL::hash_map_iterator(hash_map_iterator<Obs2T, SourcePairType> const& copyfrom)
		: current((pair_type*)copyfrom.current),
		  buckets_ref(copyfrom.buckets_ref)
	{
		static_assert(!(!std::is_const<pair_type>::value
			&& std::is_const<Obs2T>::value), "cannot copy const_iterator to iterator");
	}

	ITER_TPL_DECL
	typename ITER_DECL::pair_type* ITER_DECL::operator-> () const
	{
		return current;
	}

	ITER_TPL_DECL
	typename ITER_DECL::pair_type& ITER_DECL::operator* () const
	{
		return *current;
	}

	ITER_TPL_DECL
	ITER_DECL& ITER_DECL::operator++ ()
	{
		_ASSERT(current != nullptr);  // cannot increment a non initialized iterator.
		auto baseaddr = &buckets_ref->array[0];
		auto limit = baseaddr + buckets_ref->array.size();
		++current;
		while (current < (pair_type*)limit && buckets_ref->occup.get_at(current - (pair_type*)baseaddr) != buckstate::occupied)
			++current;
		return *this;
	}

	ITER_TPL_DECL
	ITER_DECL ITER_DECL::operator++ (int)
	{
		hash_map_iterator it = *this;
		++(*this);
		return it;
	}

	ITER_TPL_DECL
	template< typename PairT, typename SRCPairT >
	bool ITER_DECL::operator== (hash_map_iterator<PairT, SRCPairT> const& rhs) const
	{
		static_assert(std::is_same< SRCPairT, SourcePairType>::value, "can only compare equivalent iterator types");
		static_assert(std::is_same< typename std::remove_const< PairT >::type,
									typename std::remove_const< pair_type >::type >::value, "can only compare equivalent iterator types");
		return current == rhs.current && buckets_ref == rhs.buckets_ref;
	}

	ITER_TPL_DECL
	template< typename PairT, typename SRCPairT >
	bool ITER_DECL::operator!= (hash_map_iterator<PairT, SRCPairT> const& rhs) const
	{
		return !(*this == rhs);
	}

	ITER_TPL_DECL
	ITER_DECL& ITER_DECL::operator = (hash_map_iterator const& rhs)
	{
		current = rhs.current;
		buckets_ref = rhs.buckets_ref;
		return *this;
	}

#undef ITER_TPL_DECL
#undef ITER_DECL

	namespace detail
	{
		namespace
		{
			static size_t const primes[] = {
				13, 17, 23, 37, 53, 79, 113, 149, 211, 283, 383, 541, 733, 1009, 1361,
				1823, 2437, 3251, 4339, 5801, 7753, 10331, 13763, 18341, 24469, 32603, 43411,
				57829, 76991, 102497, 136481, 181693, 241861, 321947, 428531, 570389, 759223,
				1010617, 1345207, 1790501, 2383219, 3172123, 4222117, 5619701, 7479887, 9955783,
				13251233 };
		}

		// purpose of this, is when we overshot the primes[] table,
		// we use "n * 3/2 * 1.1113" as a growth factor. then round to nearest size_t.
		// so this function exists to improve a bit on the risk of having bad bucket sizes.
		inline size_t improve_primeness(size_t val)
		{
			if (val > 5 && (val % 5 == 0))  // if divisible by 5, make end by 7. exept 5, no prime number ends in a 5.
				val += 2;
			if ((val & 1) != 0)  // if even, make odd.
				++val;
			return val;
		}
	}

	static size_t next_advised_bucket_count(size_t contenance, float max_load_factor)
	{
		static size_t const cnt = _countof(detail::primes);
		size_t minbuckets = (size_t)ceil(contenance / max_load_factor);
		auto beg = &detail::primes[0];
		auto end = beg + cnt;
		auto it = std::upper_bound(beg, end, minbuckets);
		if (it == end)
			return detail::improve_primeness((size_t)(minbuckets * 1.1113f));
		_ASSERT(*it >= minbuckets);
		return *it;
	}

	enum class buckets_rounding { nearest, next_prime };

	namespace impl
	{
		enum found_status { vacant, found, notfound, full_notfound, unset };
		enum class purpose { find, place, find_and_place };

		struct statpos
		{
			found_status stat;
			size_t pos;
		};

		struct multi_pos
		{
			statpos find;   // position for find purpose
			statpos place;  // position for place purpose
		};
	}

	//============================================================================
	// class hash_map
	//============================================================================
	template< typename Key,
		      typename MappedValue,
			  typename HashFunc = std::hash<Key>,
			  typename EqualFunc = std::equal_to<Key> >
	class hash_map
	{
	public:
		// all the standard typedefs (minus allocator):
		typedef std::pair< const Key, MappedValue > value_type;
		typedef value_type const					const_value_type;
		typedef Key				key_type;		// the first template parameter(Key)
		typedef MappedValue		mapped_type;		// the second template parameter(MappedValue)
		typedef HashFunc			hasher;			// the third template parameter(HashFunc)	defaults to : std::hash<key_type>
		typedef EqualFunc		key_equal;		// the fourth template parameter(Pred)	defaults to : std::equal_to<key_type>
		typedef value_type&		reference;
		typedef value_type const& const_reference;
		typedef value_type*		pointer;
		typedef value_type const*	const_pointer;
		typedef hash_map_iterator<value_type,    value_type>			iterator;
		typedef hash_map_iterator<const_value_type, value_type>		const_iterator;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;

		//! default construction (start empty, but will resize on first insertion to 13 initial buckets)
							hash_map();
							hash_map(size_type min_num_of_init_buckets);
							hash_map(hash_map const& copyfrom);
		template <class InputIterator>
							hash_map(InputIterator first, InputIterator last);

		hash_map&			operator = (hash_map const& assignfrom);
		void				copy(hash_map const& assignfrom);

		bool				operator == (hash_map const& compare_to) const;
		bool				operator != (hash_map const& compare_to) const;

		size_type			size() const;
		bool				empty() const;
		mapped_type&			operator [] (key_type const& key);
		mapped_type const&	operator [] (key_type const& key) const;
		mapped_type&			at(const key_type& k);
		mapped_type const&	at(const key_type& k) const;
		//! non standard extension. this is more convenient than having to use make pair or typedef the value type.
		std::pair<iterator, bool> insert(key_type const& key, mapped_type const& mapped_value);
		//! standard pair insert overload
		std::pair<iterator, bool> insert(const_reference value);
		template <class InputIterator>
		void					  insert(InputIterator first, InputIterator last);  //!< range insert.
		//! emplace 0 args
		std::pair<iterator, bool> emplace(key_type const& key);
		iterator                  emplace_pos(size_type pos, key_type const& key);
		//! emplace 1 arg
		template< typename MappedTypeCompatType >
		std::pair<iterator, bool> emplace(key_type const& key, MappedTypeCompatType const& mappedconstruct);
		//! "emplace hint" (more for internal usage)
		template< typename MappedTypeCompatType >
		iterator            emplace_pos(size_type pos, key_type const& key, MappedTypeCompatType const& mappedconstruct);
		iterator			erase(const_iterator position);
		size_type			erase(key_type const& k);
		iterator			erase(const_iterator first, const_iterator last);
		bool				has_key(key_type const& tosearch) const;
		void				clear();
		void				swap(hash_map& rhs);
		float				load_factor() const;
		float				max_load_factor() const;
		void				max_load_factor(float lf);   //!< change max load factor. !: value internally clamped between 0.1 and 1.0
		void				reserve(size_type n, buckets_rounding rounding = buckets_rounding::next_prime);  //!< please indicate intended contenance (actual buckets will be policy(n / max_load_factor))
		void 				rehash(size_type n);  //!< please indicate directly number of buckets.
		key_equal			key_eq() const;
		size_type 			bucket_count() const;
		// iterator access:
		iterator			begin();
		const_iterator		begin() const;
		const_iterator		cbegin() const;
		iterator			end();
		const_iterator		end() const;
		const_iterator		cend() const;
		iterator			find(key_type const& k);
		const_iterator 		find(key_type const& k) const;
		//! non standard extension that allows some statistics
		size_type			count_buckstate_(buckstate of_value) const;

	private:
		impl::found_status determine_found_status(size_t at, key_type const& k, impl::purpose p) const;
		void determine_multi_found_status(impl::multi_pos& mp /*out*/, size_t pos, key_type const& k, impl::purpose p) const;
		impl::multi_pos find_placement(key_type const& k, impl::purpose p) const;
		size_t find_next_occupied(size_t from_incl) const;   //< if from_incl is occupied it returns from_incl.
		size_t increment_modulo_bucket_size(size_t value) const;
		size_t decrement_modulo_bucket_size(size_t value) const;
		void set_smart_deleted_state_at(size_t pos);
		bool is_in_clump(size_t pos);

		size_type count = 0;
		map_buckets<value_type> buckets;
		hasher hash_fn;
		key_equal eq_fn;
		float maxloadf = 0.7f;
#ifdef _DEBUG
		value_type* _dbgbuckets;  // help vizu in watch
		bool _antiresize_recursion = false;
#endif
	};


inline size_t increment_modulo(size_t value, size_t limit)
{
	++value;
	if (value >= limit)
		value = 0;
	return value;
}

inline size_t decrement_modulo(size_t value, size_t limit)
{
	if (value == 0)
		value = limit - 1;
	else
		--value;
	return value;
}

#define HASHMAP_TPL_DECL	template< typename Key,\
									  typename MappedValue,\
									  typename HashFunc,\
									  typename EqualFunc >

#define HASHMAP_DECL hash_map<Key, MappedValue, HashFunc, EqualFunc>

#define init_dbg_recursguarder , _antiresize_recursion(false)

	HASHMAP_TPL_DECL
	HASHMAP_DECL::hash_map()
	{}

	HASHMAP_TPL_DECL
	HASHMAP_DECL::hash_map(size_type min_num_of_init_buckets)
	{
		rehash(min_num_of_init_buckets);
	}

	HASHMAP_TPL_DECL
	HASHMAP_DECL::hash_map(hash_map const& copyfrom)
	{
		copy(copyfrom);
	}

	HASHMAP_TPL_DECL
	template <class InputIterator>
	HASHMAP_DECL::hash_map(InputIterator first, InputIterator last)
	{
		insert(first, last);
	}

	HASHMAP_TPL_DECL
	HASHMAP_DECL& HASHMAP_DECL::operator = (hash_map const& assignfrom)
	{
		clear();
		copy(assignfrom);
		return *this;
	}

	HASHMAP_TPL_DECL
	void HASHMAP_DECL::copy(hash_map const& assignfrom)
	{
		auto it = assignfrom.cbegin();
		auto end = assignfrom.cend();
		for (; it != end; ++it)
		{
			emplace(it->first, it->second);
		}
	}

	HASHMAP_TPL_DECL
	size_t HASHMAP_DECL::increment_modulo_bucket_size(size_t value) const
	{
		return increment_modulo(value, buckets.array.size());
	}

	HASHMAP_TPL_DECL
	size_t HASHMAP_DECL::decrement_modulo_bucket_size(size_t value) const
	{
		return decrement_modulo(value, buckets.array.size());
	}

	HASHMAP_TPL_DECL
	impl::found_status HASHMAP_DECL::determine_found_status(size_t at, key_type const& k, impl::purpose p) const
	{
		using namespace impl;
		_ASSERT(p != purpose::find_and_place);  // not capable of answering both at once.
		found_status st = notfound;
		if (buckets.occup.size() == 0)
			return full_notfound;
		bool occupied = buckets.occup.get_at(at) == buckstate::occupied;
		bool keyequal = occupied ? eq_fn(k, buckets.array[at].first) : false;
		if (keyequal)
			st = found;
		else if (!occupied)
		{
			// if not occupied and not empty it can only be "deleted". this is the 3rd implicit condition. a deleted bucket is a valid placement.
			bool purpose_is_place = p == purpose::place;
			bool empty = buckets.occup.get_at(at) == buckstate::empty;
			st = purpose_is_place || empty ? vacant : notfound;
		}
		return st;
	}

	HASHMAP_TPL_DECL
	inline void HASHMAP_DECL::determine_multi_found_status(impl::multi_pos& mp /*out*/, size_t pos, key_type const& k, impl::purpose p) const
	{
		using namespace impl;
		if (p == purpose::find || p == purpose::find_and_place)
		{
			mp.find.stat = determine_found_status(pos, k, purpose::find);
			mp.find.pos = pos;
		}
		if (p == purpose::place || p == purpose::find_and_place)
		{
			mp.place.stat = determine_found_status(pos, k, purpose::place);
			mp.place.pos = pos;
		}
	}

	HASHMAP_TPL_DECL
	impl::multi_pos HASHMAP_DECL::find_placement(key_type const& k, impl::purpose p) const
	{
		using namespace impl;
		multi_pos	 mp { {unset, 0}, {unset, 0} };
		size_t const limit  = buckets.array.size();
		if (limit == 0)
		{
			mp.find.stat = mp.place.stat = full_notfound;
			return mp;
		}
		size_t const h      = hash_fn(k);
		size_t loopcnt 		= 0;
		size_t pos			= h % limit;
		auto& mainstatus	= p == purpose::place ? mp.place.stat : mp.find.stat;   // the find status is stronger.
		determine_multi_found_status(mp /*out*/, pos, k, p);
		while (mainstatus == notfound && loopcnt < limit)
		{
			if (p == purpose::find_and_place && mp.place.stat == vacant)
				p = purpose::find;  // after placement found, fallback to pure find.
			// check next (linear probing):
			pos = increment_modulo(pos, limit);
			determine_multi_found_status(mp /*out*/, pos, k, p);
			++loopcnt;
		}
		if (mainstatus == notfound && loopcnt == limit)
			mp.find.stat = mp.place.stat = full_notfound;

		_ASSERT(mainstatus == vacant || mainstatus == found || mainstatus == full_notfound);  // this function's invariant.
		return mp;
	}

	HASHMAP_TPL_DECL
	size_t HASHMAP_DECL::find_next_occupied(size_t from_incl) const
	{
		size_t lim = buckets.array.size();
		size_t nextvalid = from_incl;
		size_t loop = 0;
		while (loop < lim && buckets.occup.get_at(nextvalid) != buckstate::occupied)
		{
			nextvalid = increment_modulo(nextvalid, lim);
			++loop;
		}
		if (loop == lim)
			nextvalid = lim;  // end.
		return nextvalid;
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::size_type HASHMAP_DECL::size() const
	{
		return count;
	}

	HASHMAP_TPL_DECL
	bool HASHMAP_DECL::empty() const
	{
		return size() == 0;
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::mapped_type& HASHMAP_DECL::operator [] (key_type const& key)
	{
		using namespace impl;
		auto multi_stat_pos = find_placement(key, purpose::find_and_place);
		if (multi_stat_pos.find.stat != found)  // need to insert if not found. (operator [] 's responsibility)
		{
			_ASSERT(multi_stat_pos.place.stat != unset);
			auto res = emplace_pos(multi_stat_pos.place.pos, key);
			return res->second;
		}
		_ASSERT(multi_stat_pos.find.stat == found);
		return buckets.array[multi_stat_pos.find.pos].second;
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::mapped_type const& HASHMAP_DECL::operator [] (key_type const& key) const
	{
		return at(key);
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::mapped_type& HASHMAP_DECL::at(const key_type& k)
	{
		// call const version implementation and cast return value to non const. (factorizes code better)
		return const_cast<mapped_type&>(const_cast<hash_map const*>(this)->at(k));
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::mapped_type const& HASHMAP_DECL::at(const key_type& key) const
	{
		using namespace impl;
		auto stat_pos = find_placement(key, purpose::find).find;
		if (stat_pos.stat != found)
		{
			throw std::out_of_range("try to access a non existing element");
		}
		_ASSERT(stat_pos.stat == found);
		return buckets.array[stat_pos.pos].second;
	}

	HASHMAP_TPL_DECL
	std::pair<typename HASHMAP_DECL::iterator, bool> HASHMAP_DECL::insert(key_type const& key, mapped_type const& mapped_value)
	{
		return emplace(key, mapped_value);
	}

	HASHMAP_TPL_DECL
	std::pair<typename HASHMAP_DECL::iterator, bool> HASHMAP_DECL::insert(const_reference value)
	{
		return emplace(value.first, value.second);
	}

	HASHMAP_TPL_DECL
	template <class InputIterator>
	void HASHMAP_DECL::insert(InputIterator first, InputIterator last)
	{
		std::for_each(first, last, [&](decltype(*first)& p){ insert(p); }); // C++11 style. C++14 would be 'auto&'.
	}

	HASHMAP_TPL_DECL
	std::pair<typename HASHMAP_DECL::iterator, bool> HASHMAP_DECL::emplace(key_type const& key)
	{
		return emplace(key, mapped_type());
	}

	HASHMAP_TPL_DECL
	template< typename MappedTypeCompatType >
	std::pair<typename HASHMAP_DECL::iterator, bool> HASHMAP_DECL::emplace(key_type const& key, MappedTypeCompatType const& mappedconstruct)
	{
		using namespace impl;
		auto stat_pos = find_placement(key, purpose::place).place;
		return std::make_pair(emplace_pos(stat_pos.pos, key, mappedconstruct), stat_pos.stat != found);
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::iterator HASHMAP_DECL::emplace_pos(size_type pos, key_type const& key)
	{
		return emplace_pos(pos, key, mapped_type());
	}

	HASHMAP_TPL_DECL
	template< typename MappedTypeCompatType >
	typename HASHMAP_DECL::iterator HASHMAP_DECL::emplace_pos(size_type pos, key_type const& key, MappedTypeCompatType const& mappedconstruct)
	{
		using namespace impl;
		found_status status = determine_found_status(pos, key, purpose::place);  // check the pos hint
		if (status == notfound)
		{	// it was a bad hint
			auto p = find_placement(key, purpose::place).place;
			status = p.stat;
			pos = p.pos;
		}

		if (status == found)
		{	// don't overwrite value if already inserted.
			return iterator(&buckets, pos);
		}
		else
		{   _ASSERT(status == vacant || status == full_notfound);

			if (float(count + 1) / max_load_factor() >= buckets.array.size())  // not enough space to guarantee a correct load factor
			{
				_ASSERT(!_antiresize_recursion);
				rehash(next_advised_bucket_count(count < 30000 ? (count + 1) * 2 : count * 3 / 2, max_load_factor()));
				auto p = find_placement(key, purpose::place).place;
				status = p.stat;
				pos = p.pos;
				_ASSERT(status == vacant);
			}
			_ASSERT(buckets.occup.get_at(pos) != buckstate::occupied);
			new (&buckets.array[pos]) value_type(key, mappedconstruct);  // call 1 arg constructor
			buckets.occup.set_at(pos, buckstate::occupied);
			++count;
			return iterator(&buckets, pos);
		}
	}

	// is surrounded by at least one deleted or occupied slot
	HASHMAP_TPL_DECL
	bool HASHMAP_DECL::is_in_clump(size_t pos)
	{
		_ASSERT(buckets.array.size() > 3);  // should always be true, normally the minimum size is 13.

		size_t oneafter = increment_modulo_bucket_size(pos);
		auto right_state = buckets.occup.get_at(oneafter);
		bool is_free = right_state == buckstate::empty;
		return !is_free;
	}

	// when we delete an entry, its slot can be marked empty or deleted.
	// the deleted state serves the purpose of keeping the connection between entries in clumps.
	// because of linear-probing, collisionning entries get appended on the first empty slot.
	// which means to find them later on, we need to know when the key we are looking for is not
	// in its right place later, that maybe some other key was there before and got deleted,
	// so our key maybe further on the right.
	// But, there is no need to mark this connection if the surroundings are clear from
	// probed-placed entries. To avoid "deleted" flag pollution, we can directly mark this slot empty.
	HASHMAP_TPL_DECL
	void HASHMAP_DECL::set_smart_deleted_state_at(size_t pos)
	{
		bool belongs_to_clump = is_in_clump(pos);
		buckets.occup.set_at(pos, belongs_to_clump ? buckstate::deleted : buckstate::empty);
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::iterator HASHMAP_DECL::erase(const_iterator position)
	{
		size_t pos = (value_type*)&(*position) - &buckets.array[0];
		_ASSERT(buckets.occup.get_at(pos) == buckstate::occupied);
		set_smart_deleted_state_at(pos);
		// destroy entry
		buckets.array[pos].~value_type();
		--count;
		pos = find_next_occupied(increment_modulo_bucket_size(pos));
		return iterator(&buckets, pos);
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::size_type HASHMAP_DECL::erase(key_type const& key)
	{
		auto stat_pos = find_placement(key, impl::purpose::find).find;
		if (stat_pos.stat == impl::found)
		{
			erase(const_iterator(&buckets, stat_pos.pos));
			return 1;
		}
		return 0;
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::iterator HASHMAP_DECL::erase(const_iterator first, const_iterator last)
	{
		size_t firstpos = (value_type*)&(*first) - &buckets.array[0];
		_ASSERT(buckets.occup.get_at(firstpos) == buckstate::occupied);
		auto it = iterator(&buckets, firstpos);
		while (it != last && it != end())
			it = erase(it);
		return it;
	}

	HASHMAP_TPL_DECL
	bool HASHMAP_DECL::has_key(key_type const& tosearch) const
	{
		auto st = find_placement(tosearch, impl::purpose::find).find;
		return st.stat == impl::found;
	}

	HASHMAP_TPL_DECL
	void HASHMAP_DECL::clear()
	{
		map_buckets<value_type> empty;
		buckets.swap(empty);
		count = 0;
	}

	HASHMAP_TPL_DECL
	void HASHMAP_DECL::swap(hash_map& rhs)
	{
		std::swap(count, rhs.count);
		buckets.swap(rhs.buckets);
		std::swap(hash_fn, rhs.hash_fn);
		std::swap(eq_fn, rhs.eq_fn);
#ifdef _DEBUG
		_dbgbuckets = buckets.array.size() ? &buckets.array[0] : nullptr;
#endif
	}

	HASHMAP_TPL_DECL
	float HASHMAP_DECL::load_factor() const
	{
		return count / (float)buckets.array.size();
	}

	HASHMAP_TPL_DECL
	float HASHMAP_DECL::max_load_factor() const
	{
		return maxloadf;
	}

	HASHMAP_TPL_DECL
	void HASHMAP_DECL::max_load_factor(float lf)
	{
		maxloadf = std::min(std::max(lf, 0.1f), 1.0f);
	}

	HASHMAP_TPL_DECL
	void HASHMAP_DECL::reserve(size_type n, buckets_rounding rounding /*= buckets_rounding::next_prime*/)  // intended contenance
	{
		size_t numbuckets;
		if (rounding == buckets_rounding::next_prime)
			numbuckets = next_advised_bucket_count(n, max_load_factor());
		else
			numbuckets = size_t((float)n / max_load_factor());
		rehash(numbuckets);
	}

	HASHMAP_TPL_DECL
	void HASHMAP_DECL::rehash(size_type n)  // num of buckets
	{
		// we need to respect some mininum size criterias as invariants of map, or we'll run into bugs.
		// min size 3 must be respected for the erase method to work.
		// and the sizing must be adapted to the contents.
		size_t minbuckets_for_currentsize = std::max<size_t>(3, size_t(ceil((float)size() / max_load_factor())));
		if (n < minbuckets_for_currentsize)
			n = minbuckets_for_currentsize;
		if (n != buckets.array.size())
		{
			map_buckets<value_type> old_buckets;
			old_buckets.swap(buckets);
			count = 0;
			// set new size:
			buckets.resize(n);
			_ASSERT(buckets.all_occupancy_is_empty());
			// iterate over old buckets and re-insert everything:
			size_t it = 0;
			size_t lim = old_buckets.array.size();
			DBG_NLY(_antiresize_recursion = true);
			while (it != lim)
			{
				if (old_buckets.occup.get_at(it) == buckstate::occupied)
					emplace(old_buckets.array[it].first, old_buckets.array[it].second);
				++it;
			}
			DBG_NLY(_antiresize_recursion = false;)
			DBG_NLY(_dbgbuckets = &buckets.array[0];)
		}
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::key_equal HASHMAP_DECL::key_eq() const
	{
		return eq_fn;
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::size_type HASHMAP_DECL::bucket_count() const
	{
		return buckets.array.size();
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::iterator HASHMAP_DECL::begin()
	{
		return iterator(&buckets, find_next_occupied(0));
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::const_iterator HASHMAP_DECL::begin() const
	{
		return cbegin();
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::const_iterator HASHMAP_DECL::cbegin() const
	{
		return const_iterator(const_cast<map_buckets<value_type>*>(&buckets), find_next_occupied(0));
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::iterator HASHMAP_DECL::end()
	{
		return iterator(&buckets, buckets.array.size());
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::const_iterator HASHMAP_DECL::end() const
	{
		return cend();
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::const_iterator HASHMAP_DECL::cend() const
	{
		return const_iterator(const_cast<map_buckets<value_type>*>(&buckets), buckets.array.size());
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::iterator HASHMAP_DECL::find(key_type const& k)
	{
		auto sttpos = find_placement(k, impl::purpose::find).find;
		return iterator(&buckets, sttpos.stat == impl::found ? sttpos.pos : buckets.array.size());
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::const_iterator HASHMAP_DECL::find(key_type const& k) const
	{
		auto sttpos = find_placement(k, impl::purpose::find).find;
		return const_iterator(&buckets, sttpos.stat == impl::found ? sttpos.pos : buckets.array.size());
	}

	HASHMAP_TPL_DECL
	typename HASHMAP_DECL::size_type HASHMAP_DECL::count_buckstate_(buckstate of_value) const
	{
		size_t cnt = 0;
		for (size_t i = 0; i < buckets.array.size(); ++i)
			if (buckets.occup.get_at(i) == of_value)
				++cnt;
		return cnt;
	}

#undef HASHMAP_TPL_DECL
#undef HASHMAP_DECL
#undef DBG_NLY
}

#ifdef do_undef_countof_at_file_end
# undef _countof
#endif

#endif
