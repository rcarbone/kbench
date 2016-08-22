#ifndef __HASHIT__
#define __HASHIT__

#define CHAIN_H 0U
#define OADDRESS_H 1U
#define OVERFLOW_H 2U


#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct shash_t;
typedef struct shash_t *hash_t;

hash_t hashit_create(uint32_t, size_t, uint32_t(*)(), int(*)(void *, void *), unsigned int);
int hashit_insert(hash_t, void *, void *);
int hashit_delete(hash_t, void *);
int hashit_replace(hash_t, void *, void *);
void *hashit_lookup(hash_t, void *);
int hashit_destroy(hash_t);
/* Accesors */
void **hashit_getkeys(hash_t);
void **hashit_getvalues(hash_t);
size_t hashit_tablesize(hash_t);
size_t hashit_size(hash_t);

#ifdef __cplusplus
}
#endif
#endif 
