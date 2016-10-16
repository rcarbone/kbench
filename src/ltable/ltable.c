#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "ltable.h"

#define SHORTSTR_LEN 128

struct pool_node {
    size_t nodesz;
    struct pool_node *next;
};

struct pool {
    struct pool_node *node;
    struct pool_node *freenode;
};

#define MAXBITS      30
#define MAXASIZE	(1 << MAXBITS)

/* use at most ~(2^LUAI_HASHLIMIT) bytes from a string to compute its hash*/
#define STR_HASHLIMIT		5

union ltable_Hash {
    double f;
    const void *p;
    long int i;
    uint8_t l_p[4];
};

struct ltable_value {
    bool setted;
};

struct ltable_node {
    struct ltable_node *next;
    struct ltable_key key;
    struct ltable_value value;
    /* follow vmemsz space*/
};

struct ltable {
    size_t vmemsz;
    struct ltable_value *array;
    struct ltable_node *node;
    int sizearray;
    uint8_t lsizenode;          /* log2 of size of `node' array */
    struct pool pool;
    unsigned int seed;
    int lastfree;
};


/*
** `module' operation for hashing (size is always a power of 2)
*/
#define lmod(s,size)  ((int)((s) & ((size)-1)))

#define twoto(i) (1<<(i))
#define gnext(n)    ((n)->next)
#define sizenode(t)	(1 << ((t)->lsizenode))
#define inarray(t, idx) ((idx)>=0 && (idx) < (t)->sizearray)
#define nodememsz(t) (t->vmemsz + sizeof(struct ltable_node))
#define valmemsz(t)  (t->vmemsz + sizeof(struct ltable_value))

/*
** {=============================================================
** Pool
** ==============================================================
*/

static void
pool_init(struct pool *p) {
    p->node = NULL;
    p->freenode = NULL;
}

static void*
pool_alloc(struct pool *p, size_t sz) {
    struct pool_node **np = &p->freenode;
    struct pool_node *n = NULL;
    while (*np) {
        if ((*np)->nodesz >= sz) {
            n = *np;
            *np = (*np)->next;
            break;
        }
        np = &(*np)->next;
    }
    if (!n) {
        if (sz < SHORTSTR_LEN) sz = SHORTSTR_LEN;
        n = (struct pool_node*)malloc(sz + sizeof(struct pool_node));
        n->nodesz = sz;
    }
    n->next = p->node;
    p->node = n;
    return n+1;
}

static void
pool_free(struct pool *p, struct pool_node *node) {
    struct pool_node **np = &p->node;
    node--;

    while(*np) {
        if (*np == node) {
            *np = (*np)->next;
            break;
        }
        np = &(*np)->next;
    }

    node->next = p->freenode;
    p->freenode = node;
}

static void
pool_release(struct pool *p) {
    struct pool_node *nextn;
    struct pool_node *n = p->node;
    while(n) {
        nextn = n->next;
        free(n);
        n = nextn;
    }
    n = p->freenode;
    while(n) {
        nextn = n->next;
        free(n);
        n = nextn;
    }
}


/*
** }=============================================================
*/

static inline bool
isnil(const struct ltable_value *v) {
    return !v->setted;
}

static inline bool
isnilnode(const struct ltable_node *n) {
    return isnil(&n->value);
}

static inline struct ltable_value*
_garray(const struct ltable* t, int idx) {
    return (struct ltable_value*)(((char*)t->array) + valmemsz(t)*idx);
}

static inline struct ltable_node*
_gnode(const struct ltable* t, int idx) {
    return (struct ltable_node*)(((char*)t->node) + nodememsz(t)*idx);
}

static inline struct ltable_node*
_gnodex(const struct ltable*t, int idx, void* n) {
    return (struct ltable_node*)(((char*)n) + nodememsz(t)*idx);
}

static inline void
_cpyval(struct ltable *t, struct ltable_value *dest, const struct ltable_value *src) {
    memcpy(dest, src, valmemsz(t));
}

static inline void
_cpynode(struct ltable *t, struct ltable_node *dest, const struct ltable_node *src) {
    memcpy(dest, src, nodememsz(t));
}

static inline void*
_gud(struct ltable_value* v) {
    if (v == NULL || isnil(v))
        return NULL;
    else
        return v+1;
}

static struct ltable_node*
_hashnode(struct ltable *t, unsigned int h) {
    return _gnode(t, h & (sizenode(t)-1));
}

static void
_rehash(struct ltable* t, const struct ltable_key *ek);

static struct ltable_value *
_set(struct ltable* t, const struct ltable_key *key);


int
_floorlog2 (unsigned int x) {
  static const unsigned char log_2[256] = {
      0,0,1,1,2,2,2,2,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
      5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
      6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
      6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
      7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
      7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
      7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
      7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
  };
  int l = 0;
  while (x >= 256) { l += 8; x >>= 8; }
  return l + log_2[x];
}

int
_ceillog2 (unsigned int x) {
  static const unsigned char log_2[256] = {
    0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
    6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
  };
  int l = 0;
  x--;
  while (x >= 256) { l += 8; x >>= 8; }
  return l + log_2[x];
}

void
_cpykey(struct ltable *t, struct ltable_key *dest, const struct ltable_key *src) {
    *dest = *src;
    if (dest->type == LTABLE_KEYSTR) {
        size_t l = strlen(src->v.s)+1;
        char *sp = pool_alloc(&t->pool, l);
        memcpy(sp, src->v.s, l);
        dest->v.s = sp;
    }
}

bool
_eqkey(const struct ltable_key *key, const struct ltable_key *nkey) {
    if (key->type != nkey->type)
        return false;

    switch (key->type) {
    case LTABLE_KEYSTR:
        return !strcmp(key->v.s, nkey->v.s);
    case LTABLE_KEYINT:
        return key->v.i == nkey->v.i;
    case LTABLE_KEYNUM:
        return key->v.f == nkey->v.f;
    default:                    /* keyobj */
        return key->v.p == nkey->v.p;
    }
}

unsigned int
_strhash (const char *str, unsigned int seed) {
    size_t l = strlen(str);
    unsigned int h = seed ^ ((unsigned int)l);
    size_t l1;
    size_t step = (l >> STR_HASHLIMIT) + 1;
    for (l1 = l; l1 >= step; l1 -= step)
        h = h ^ ((h<<5) + (h>>2) + ((uint8_t)(str[l1 - 1])));
    return h;
}

unsigned int
_numhash (union ltable_Hash *u) {
    int i = u->l_p[0] + u->l_p[1] + u->l_p[2] + u->l_p[3];

    if (i < 0) {
        if (((unsigned int)i) == 0u - i)  /* use unsigned to avoid overflows */
            i = 0;  /* handle INT_MIN */
        i = -i;  /* must be a positive value */
    }
    return i;
}

/*
** returns the index for `key' if `key' is an appropriate key to live in
** the array part of the table, -1 otherwise.
*/
static int
arrayindex (const struct ltable_key *key) {
  if (key->type == LTABLE_KEYINT) {
      return key->v.i;
  }
  return -1;  /* `key' did not match some condition */
}

static struct ltable_node *
mainposition(struct ltable* t, const struct ltable_key* key) {
    unsigned int h;
    if (key->type == LTABLE_KEYSTR)
        h = _strhash(key->v.s, t->seed);
    else {
        union ltable_Hash u;
        memset(&u, 0, sizeof(u));

        switch(key->type) {
        case LTABLE_KEYNUM:
            u.f = key->v.f; break;
        case LTABLE_KEYINT:
            u.i = key->v.i; break;
        default:                /* LTABLE_KEYOBJ  */
            u.p = key->v.p; break;
        }

        h = _numhash(&u);
    }
    return _hashnode(t, h);
}

static struct ltable_node*
_getfreepos(struct ltable* t) {
    while (t->lastfree > 0) {
        t->lastfree--;
        if (isnilnode(_gnode(t, t->lastfree)))
            return _gnode(t, t->lastfree);
    }
    return NULL;  /* could not find a free place */
}

static struct ltable_node *
_hashget(struct ltable* t, const struct ltable_key * key) {
    struct ltable_node *node = mainposition(t, key);
    while (node) {
        if (!isnilnode(node) && _eqkey(&node->key, key))
            break;
        else
            node = gnext(node);
    }
    return node;
}

static struct ltable_value *
_get(struct ltable* t, const struct ltable_key * key) {
    int idx = arrayindex(key);
    if (inarray(t, idx)) {  /* in array part? */
        struct ltable_value* val = _garray(t, idx);
        return isnil(val) ? NULL : val;
    }

    struct ltable_node *node = _hashget(t, key);
    return node ? &node->value : NULL;    
}

static struct ltable_value *
_hashset(struct ltable* t, const struct ltable_key *key) {
    struct ltable_node *mp = mainposition(t, key);
    if (!isnilnode(mp)){      /* main position is taken? */
        struct ltable_node *othern;
        struct ltable_node *freen = _getfreepos(t);
        if (!freen) {
            _rehash(t, key);
            return _set(t, key);
        }
        othern = mainposition(t, &mp->key);
        if (othern != mp) { /* is colliding node out of its main position? */
            /* yes; move colliding node into free position */
            while (gnext(othern) != mp)
                othern = gnext(othern); /* find previous */
            gnext(othern) = freen;
            _cpynode(t, freen, mp); /* copy colliding node into free pos. (mp->next also goes) */
            gnext(mp) = NULL;
        }
        else { /* colliding node is in its own main position */
            /* new node will go into free position */
            gnext(freen) = gnext(mp);
            gnext(mp) = freen;
            mp = freen;
        }
    }
    _cpykey(t, &mp->key, key);
    mp->value.setted = true;
    return &mp->value;
}

static struct ltable_value *
_set(struct ltable* t, const struct ltable_key *key) {
    int idx = arrayindex(key);
    if (inarray(t, idx)) {  /* in array part? */
        struct ltable_value * val = _garray(t, idx);
        val->setted = true;
        return val;
    } else {
        return _hashset(t, key);
    }
}

/*
** {=============================================================
** Rehash
** ==============================================================
*/
static int
computesizes (int nums[], int *narray) {
    int i;
    int twotoi;  /* 2^i */
    int a = 0;  /* number of elements smaller than 2^i */
    int na = 0;  /* number of elements to go to array part */
    int n = 0;  /* optimal size for array part */
    for (i = 0, twotoi = 1;i<=MAXBITS; i++, twotoi *= 2) {
        a += nums[i];
        if (a && a >= twotoi/2) {  /* at least half elements present? */
            n = twotoi;  /* optimal size (till now) */
            na = a;  /* all elements smaller than n will go to array part */
        }
        if (*narray == a) break;
    }
    *narray = n;
    return na;
}

static int
countint (const struct ltable_key *key, int *nums) {
    int k = arrayindex(key);
    if (k<0 || k > MAXASIZE)
        return 0;
    
    if (k==0) 
        nums[0]++;
    else
        nums[_floorlog2(k)+1]++;
    return 1;
}

static int
numusearray (const struct ltable *t, int *nums) {
    int lg;
    int ause = 0;  /* summation of `nums' */
    int i = 0;  /* count to traverse all array keys. */
    for (lg=0; lg<=MAXBITS; lg++) {  /* for each slice */
        int lc = 0;  /* counter */
        int lim = twoto(lg);
        if (lim > t->sizearray) {
            lim = t->sizearray;  /* adjust upper limit */
            if (i >= lim) break;  /* no more elements to count */
        }
        /* count elements in range [2^(lg-1), 2^lg) */
        for (; i < lim; i++) {
            if (!isnil(_garray(t, i))) lc++;
        }
        nums[lg] += lc;
        ause += lc;
    }
    return ause;
}

static int
numusehash (const struct ltable *t, int *nums, int *pnasize) {
    int totaluse = 0;  /* total number of elements */
    int ause = 0;  /* summation of `nums' */
    int i;
    for (i=0;i<sizenode(t);i++) {
        struct ltable_node *n = _gnode(t, i);
        if (!isnilnode(n)) {
            ause += countint(&n->key, nums);
            totaluse++;
        }
    }
    *pnasize += ause;
    return totaluse;
}


void
_resize_node(struct ltable *t, int size) {
    int lsize = size > 0 ? _ceillog2(size) : 0; /* at least one node */
    if (lsize > MAXBITS)
        assert(0);
    size = twoto(lsize);
    int memsz = nodememsz(t)*size;
    t->node = malloc(memsz);
    memset(t->node, 0, memsz);
    t->lsizenode = (uint8_t)lsize;
    t->lastfree = size; /* all positions are free */
}

void
_resize_array(struct ltable *t, int nasize) {
    int oldasize = t->sizearray;
    t->sizearray = nasize;
    t->array = realloc(t->array, valmemsz(t) * nasize);
    if(nasize > oldasize) /* set growed part to zero */
        memset(_garray(t, oldasize), 0, valmemsz(t) * (nasize-oldasize));
}

void
_resize(struct ltable *t, int nasize, int nhsize) {
    int i;
    int oldasize = t->sizearray;
    int oldhsize = t->lsizenode;

    struct ltable_node *nold = t->node;  /* save old hash ... */

    /* resize hash part */
    _resize_node(t, nhsize);

    /* resize array part */
    if (nasize < oldasize) {  /* array part must shrink? */
        /* re-insert elements from vanishing slice */
        for (i=nasize; i<oldasize; i++) { /* insert extra array part to hash */
            if (!isnil(_garray(t, i))) {
                struct ltable_key nkey;
                ltable_intkey(&nkey, i);
                struct ltable_value *val = _hashset(t, &nkey);
                _cpyval(t, val, _garray(t, i));
            }
        }
    }

    _resize_array(t, nasize);

    /* re-insert elements from hash part */
    if (nold != NULL) {         /* not in init? */
        for (i = twoto(oldhsize) - 1; i >= 0; i--) {
            struct ltable_node *old = _gnodex(t, i, nold);
            if (!isnilnode(old)) {
                struct ltable_value *val = _set(t, &old->key);
                _cpyval(t, val, &old->value);
            }
        }
        /* free old hash part */
        free(nold);
    }
}


static void
_rehash(struct ltable* t, const struct ltable_key *ek) {
    int nasize, na;
    int nums[MAXBITS+1];  /* nums[i] = number of keys with 2^(i-1) <= k < 2^i */
    int i;
    int totaluse;
    for (i=0; i<=MAXBITS; i++) nums[i] = 0;  /* reset counts */
    nasize = numusearray(t, nums);  /* count keys in array part */
    totaluse = nasize;  /* all those keys are integer keys */
    totaluse += numusehash(t, nums, &nasize);  /* count keys in hash part */
    /* count extra key */
    nasize += countint(ek, nums);
    totaluse++;
    /* compute new size for array part */
    na = computesizes(nums, &nasize);
    /* resize the table to new computed sizes */
    _resize(t, nasize, totaluse - na);
}

/*
** }=============================================================
*/


struct ltable*
ltable_create(size_t vmemsz, unsigned int seed) {
    struct ltable* t = malloc(sizeof(struct ltable));

    t->vmemsz = vmemsz;
    t->array = NULL;
    t->node = NULL;
    t->lastfree = -1;
    t->sizearray = 0;
    t->lsizenode = 0;          /* log2 of size of `node' array */
    t->seed = seed == 0 ? LTABLE_SEED : seed;
    pool_init(&t->pool);

    _resize(t, 0, 1);
    return t;
}

void
ltable_release(struct ltable *t) {
    free(t->node);
    free(t->array);
    pool_release(&t->pool);
}

void
ltable_resize(struct ltable *t, int nasize, int nhsize) {
    _resize(t, nasize, nhsize);
}

void*
ltable_get(struct ltable *t, const struct ltable_key* key) {
    struct ltable_value *val = _get(t, key);
    return _gud(val);
}

void*
ltable_set(struct ltable* t, const struct ltable_key* key) {
    struct ltable_value *val = _get(t, key);
    if (!val) val = _set(t, key);
    return _gud(val);
}

void*
ltable_getn(struct ltable* t, int i) {
    if (inarray(t, i)) {
        struct ltable_value *val = _garray(t, i);
        return _gud(val);
    } 

    struct ltable_key k;
    ltable_intkey(&k, i);
    struct ltable_node *node = _hashget(t, &k);
    if (node)
        return _gud(&node->value);
    return NULL;
}

void
ltable_del(struct ltable* t, const struct ltable_key* key) {
    if (key->type == LTABLE_KEYSTR) {
        struct ltable_node *node = _hashget(t, key);
        if (node) {
            node->value.setted = false;
            /* free string key */
            pool_free(&t->pool, (struct pool_node*)node->key.v.s);
            node->key.v.s = NULL;
        }
    } else {
        struct ltable_value *val = _get(t, key);
        if (val) val->setted = false;
    }
}

void *
ltable_next(struct ltable *t, unsigned int *ip, struct ltable_key *key) {
    assert(*ip >= 0);
    int nsz = sizenode(t);
    struct ltable_value * val = NULL;

    int i = *ip;
    for (;i < t->sizearray; i++) { /* search array part */
        val = _garray(t, i);
         if (!isnil(val)) {
            if (key) {
                key->type = LTABLE_KEYINT;
                key->v.i = i;
            }
            break;
        }
    }
    if (i >= t->sizearray)
        for (;i < nsz + t->sizearray; i++) { /* search hash part */
            struct ltable_node * node = _gnode(t, i - t->sizearray);
            if (!isnilnode(node)) {
                if (key) *key = node->key;
                val = &node->value;
                break;
            }
        }

    *ip = i+1;
    return _gud(val);
}

inline struct ltable_key*
ltable_numkey(struct ltable_key *key, double k) {
    key->type = LTABLE_KEYNUM;
    key->v.f  = k;

    return key;
}

inline struct ltable_key*
ltable_strkey(struct ltable_key *key, const char* k) {
    key->type = LTABLE_KEYSTR;
    key->v.s  = k;

    return key;
}

inline struct ltable_key*
ltable_intkey(struct ltable_key *key, long int k) {
    key->type = LTABLE_KEYINT;
    key->v.i  = k;
    return key;
}

inline struct ltable_key*
ltable_objkey(struct ltable_key *key, const void *p) {
    key->type = LTABLE_KEYOBJ;
    key->v.p  = p;
    return key;
}

/* end of ltable.c */
