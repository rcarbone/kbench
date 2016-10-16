/*
 * judy_open:	open a new judy array returning a judy object
 * judy_close:	close an open judy array, freeing all memory
 *
 * judy_cell:	insert a string into the judy array, return cell pointer
 * judy_del:	delete the key and cell for the current stack entry
 *
 * judy_slot:	retrieve the cell pointer, or return NULL for a given key
 * judy_key:	retrieve the string value for the most recent judy query
 *
 * judy_end:	retrieve the cell pointer for the last string in the array
 * judy_nxt:	retrieve the cell pointer for the next string in the array
 * judy_prv:	retrieve the cell pointer for the prev string in the array
 *
 * judy_clone:	clone an open judy array, duplicating the stack
 * judy_data:	allocate data memory within judy array for external use
 * judy_strt:	retrieve the cell pointer greater than or equal to given key
 */


#include <stdlib.h>
#include <memory.h>
#include <string.h>

#ifdef linux
#define _FILE_OFFSET_BITS 64
#define _LARGEFILE_SOURCE
#define __USE_FILE_OFFSET64

#include <endian.h>
#else
#ifdef __BIG_ENDIAN__
#ifndef BYTE_ORDER
#define BYTE_ORDER 4321
#endif
#else
#ifndef BYTE_ORDER
#define BYTE_ORDER 1234
#endif
#endif
#ifndef BIG_ENDIAN
#define BIG_ENDIAN 4321
#endif
#endif

typedef unsigned char uchar;
typedef unsigned int uint;

#define PRIuint	"u"

#if defined(__LP64__)    || \
  defined(__x86_64__)    || \
  defined(__amd64__)     || \
  defined(_WIN64)        || \
  defined(__sparc64__)   || \
  defined(__arch64__)    || \
  defined(__powerpc64__) || \
  defined (__s390x__)

// defines for 64 bit

typedef unsigned long long judyvalue;
typedef unsigned long long JudySlot;

#define JUDY_key_mask    (0x07)
#define JUDY_key_size    8
#define JUDY_slot_size   8
#define JUDY_span_bytes  (3 * JUDY_key_size)
#define JUDY_span_equiv  JUDY_2
#define JUDY_radix_equiv JUDY_8

#define PRIjudyvalue "llu"

#else

// defines for 32 bit

typedef uint judyvalue;
typedef uint JudySlot;

#define JUDY_key_mask    (0x03)
#define JUDY_key_size    4
#define JUDY_slot_size   4
#define JUDY_span_bytes  (7 * JUDY_key_size)
#define JUDY_span_equiv  JUDY_4
#define JUDY_radix_equiv JUDY_8

#define PRIjudyvalue	"u"

#endif

#define JUDY_mask (~(JudySlot)0x07)


typedef struct {
	void *seg;		// next used allocator
	uint next;		// next available offset
} JudySeg;

typedef struct {
	JudySlot next;		// judy object
	uint off;		// offset within key
	int slot;		// slot within object
} JudyStack;

typedef struct {
	JudySlot root[1];	// root of judy array
	void **reuse[8];	// reuse judy blocks
	JudySeg *seg;		// current judy allocator
	uint level;		// current height of stack
	uint max;		// max height of stack
	uint depth;		// number of Integers in a key, or zero for string keys
	JudyStack stack[1];	// current cursor
} Judy;




void * judy_open (uint max, uint depth);
void judy_close (Judy * judy);

JudySlot * judy_cell (Judy * judy, uchar * buff, uint max);
JudySlot * judy_del (Judy * judy);

JudySlot * judy_slot (Judy * judy, uchar * buff, uint max);
uint judy_key (Judy * judy, uchar * buff, uint max);

void * judy_alloc (Judy * judy, uint type);
void * judy_data (Judy * judy, uint amt);
void * judy_clone (Judy * judy);

void judy_free (Judy * judy, void * block, int type);
JudySlot * judy_promote (Judy * judy, JudySlot * next, int idx, judyvalue value, int keysize);
void judy_radix (Judy * judy, JudySlot * radix, uchar * old, int start, int slot, int keysize, uchar key, uint depth);
void judy_splitnode (Judy * judy, JudySlot * next, uint size, uint keysize, uint depth);

JudySlot * judy_first (Judy * judy, JudySlot next, uint off, uint depth);
JudySlot * judy_last (Judy * judy, JudySlot next, uint off, uint depth);
JudySlot * judy_end (Judy * judy);
JudySlot * judy_nxt (Judy * judy);
JudySlot * judy_prv (Judy * judy);

JudySlot * judy_strt (Judy * judy, uchar * buff, uint max);
void judy_splitspan (Judy * judy, JudySlot * next, uchar * base);
