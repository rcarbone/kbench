#ifndef LTABLE_H
#define LTABLE_H

#include <stdbool.h>

#define LTABLE_SEED        11

#define LTABLE_KEYNUM      1
#define LTABLE_KEYINT      2
#define LTABLE_KEYSTR      3
#define LTABLE_KEYOBJ      4

#define ltable_keytype(key) ((key)->type)
#define ltable_keyval(key)    ((key)->v)

struct ltable_key {
    int type;
    union {
        double f;
        long int i;
        const void * p;
        const char*  s;
    } v;
};


struct ltable;

struct ltable*  ltable_create(size_t vmemsz, unsigned int seed);
void  ltable_release(struct ltable *);
void  ltable_resize(struct ltable *t, int nasize, int nhsize);
void* ltable_next(struct ltable *t, unsigned int *ip, struct ltable_key *key);

void* ltable_get(struct ltable* t, const struct ltable_key* key);
void* ltable_set(struct ltable* t, const struct ltable_key* key);
void* ltable_getn(struct ltable* t, int i);
void  ltable_del(struct ltable* t, const struct ltable_key* key);

struct ltable_key* ltable_numkey(struct ltable_key *key, double k);
struct ltable_key* ltable_strkey(struct ltable_key *key, const char* k);
struct ltable_key* ltable_intkey(struct ltable_key *key, long int k);
struct ltable_key* ltable_objkey(struct ltable_key *key, const void *p);

#endif
