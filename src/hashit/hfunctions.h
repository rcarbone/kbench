#ifndef __HFUNCTIONS__
#define __HFUNCTIONS__

#define BOB_HASH	bob_hash
#define ONEAT_HASH	oneatatime_hash

uint32_t bob_hash(unsigned char *, unsigned long);
uint32_t oneatatime_hash(unsigned char *, size_t);

#endif
