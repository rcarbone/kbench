/******************************************************************************
 * 
 *  Hash functions for use with the hashit library.
 * Bob hash function has been written by Bob Jenkins, and the other hash
 * functions are also taken from his web page
 * 
 * See http://burtleburtle.net/bob/hash/doobs.html 
 *     http://burtleburtle.net/bob/hash/evahash.html
 * to find about his author and more info about hash functions and tables
 * 
 ******************************************************************************/

#include <string.h>
#include <stdint.h>


#define mix(a,b,c) \
{ \
  a -= b; a -= c; a ^= (c >> 13); \
  b -= c; b -= a; b ^= (a << 8); \
  c -= a; c -= b; c ^= (b >> 13); \
  a -= b; a -= c; a ^= (c >> 12);  \
  b -= c; b -= a; b ^= (a << 16); \
  c -= a; c -= b; c ^= (b >> 5); \
  a -= b; a -= c; a ^= (c >> 3);  \
  b -= c; b -= a; b ^= (a << 10); \
  c -= a; c -= b; c ^= (b >> 15); \
}


uint32_t bob_hash(unsigned char *k, unsigned long length)
{
   unsigned long a,b,c,len;

   /* Set up the internal state */
   len = length;
   a = b = c = 0x9e3779b9;  /* the golden ratio; an arbitrary value */

   /* Handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((unsigned long)k[1] << 8) +((unsigned long)k[2] << 16) +((unsigned long)k[3] << 24));
      b += (k[4] +((unsigned long)k[5] << 8) +((unsigned long)k[6] << 16) +((unsigned long)k[7] << 24));
      c += (k[8] +((unsigned long)k[9] << 8) +((unsigned long)k[10]<< 16)+((unsigned long)k[11] << 24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /* Handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
       case 11: c+=((unsigned long)k[10] << 24);
       case 10: c+=((unsigned long)k[9]  << 16);
       case 9 : c+=((unsigned long)k[8]  << 8);
       /* the first byte of c is reserved for the length */
       case 8 : b+=((unsigned long)k[7] << 24);
       case 7 : b+=((unsigned long)k[6] << 16);
       case 6 : b+=((unsigned long)k[5] << 8);
       case 5 : b+=k[4];
       case 4 : a+=((unsigned long)k[3] << 24);
       case 3 : a+=((unsigned long)k[2] << 16);
       case 2 : a+=((unsigned long)k[1] << 8);
       case 1 : a+=k[0];
   }
   mix(a,b,c);
   
   return c;
}


/* One-at-a-time hash */
uint32_t oneatatime_hash(unsigned char *key, size_t len)
{
  uint32_t hash=0;
  size_t i;

  for (i=0; i <len; ++i)
  {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  
  return hash;
} 

