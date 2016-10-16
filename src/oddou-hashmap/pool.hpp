/*** Lightness1024! (V.Oddou)       ***/
/*** Copyright 08/2014 Vivien Oddou ***/

/*** licensing (specific only to pool.hpp):
- Do What the Fuck You Want to Public License. (http://www.wtfpl.net/)
***/
/***
disclaimer 

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely.
***/

#ifndef POOL_SERHUM_INCLUDEGUARD_L1024_82014
#define POOL_SERHUM_INCLUDEGUARD_L1024_82014 1

#include <algorithm>

#ifndef _ASSERT
# include <assert.h>
# define _ASSERT(a) assert(a)
#endif

namespace container
{
	namespace detail
	{
		struct uninitialized_space
		{
			uninitialized_space(uninitialized_space const&) = delete;
			uninitialized_space(uninitialized_space&&) = delete;

			uninitialized_space()
				: zone(nullptr),
				  slots(0)
			{}

			~uninitialized_space()
			{
				clear();
			}

			char* zone;
			size_t slots;

			template< typename T >
			void alloc_space(size_t size)
			{
				_ASSERT(zone == nullptr);
				zone = new char[sizeof(T) * size];
				slots = size;
			}

			void clear()
			{
				if (zone != nullptr)
					delete[] zone;
				zone = nullptr;
				slots = 0;
			}

			void swap(uninitialized_space& rhs)
			{
				std::swap(zone, rhs.zone);
				std::swap(slots, rhs.slots);
			}
			
		};
	}

	template< typename T >
	class pool
	{
	public:

		T& at(size_t position)
		{
			_ASSERT(position < memory.slots);
			return *reinterpret_cast<T*>(&memory.zone[sizeof(T)* position]);
		}

		T const& at(size_t position) const
		{
			_ASSERT(position < memory.slots);
			return *reinterpret_cast<T*>(&memory.zone[sizeof(T)* position]);
		}

		T& operator[](size_t position)
		{
			return at(position);
		}

		T const& operator[](size_t position) const
		{
			return at(position);
		}

		size_t size() const { return memory.slots; }
		
		void resize(size_t n) { memory.alloc_space<T>(n); }

		void swap(pool& r)
		{
			memory.swap(r.memory);
		}

	private:
		detail::uninitialized_space memory;
	};
}

#endif // #define POOL_SERHUM_INCLUDEGUARD_L1024_82014 1
