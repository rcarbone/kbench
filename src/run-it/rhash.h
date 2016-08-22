#include <stdint.h>


/* Stolen from java 1.4 source (as found in Niels Provos's hash table) */
static inline unsigned java_hash (unsigned h)
{
  h += ~(h << 9);
  h ^=  ((h >> 14) | (h << 18)); /* >>> */
  h +=  (h << 4);
  h ^=  ((h >> 10) | (h << 22)); /* >>> */
  return h;
}


/* Basic string hash function from Python (as found in Niels Provos's hash table) */
static inline unsigned python_hash (const char * s)
{
  unsigned h;
  const unsigned char * cp = (const unsigned char *) s;
  h = * cp << 7;
  while (* cp)
    h = (1000003 * h) ^ * cp ++;

  /* This conversion truncates the length of the string, but that's ok */
  h ^= (unsigned) (cp - (const unsigned char *) s);

  return h;
}


/*
 * MurmurHash3
 * https://github.com/aappleby/smhasher
 */
static inline uint32_t MurmurHash3 (uint32_t h)
{
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;
  return h;
}
