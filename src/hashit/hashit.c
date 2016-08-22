/******************************************************************************
 *
 *  Filename: hashit.c
 *  Description: Generic hash library
 *
 *           Copyright (C) 2002-2007  David Gómez <david@pleyades.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *****************************************************************************/

#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <assert.h>

#include "hashit.h"
#include "hfunctions.h"


/********************************************************** Structures *******/
struct shash_t {
	/* Common fields for all hash tables types */
	size_t tsize;                  /* Table size */
	size_t ksize;                  /* Key size is fixed at creation time */
	size_t nelems;                 /* Number of elements in the hash table */
	struct hash_ops *h_ops;
	uint32_t (*hash_fn)(unsigned char *, unsigned long);
	int (*compare_fn)(void *, void *);
	union {
		struct elem **chtable;     /* Chain hash (ch) */
		struct oaelem *oatable;    /* Open Address hash (oa) */
		struct ov *ov;             /* Hash with overflow area (ov) */
	} cm;                          /* Data for the various collision methods */
};

/* Elem is used both for chain and overflow hash */
struct elem {
	void *key;
	void *data;
	struct elem *next;
};

/* Open Address */
struct oaelem {
	void *key;
	void *data;
};

/* Overflow */
struct ov {
	struct elem *ovtable;
	struct elem *ovarea;
	uint32_t cachedidx;     	/* Cached index for fast inserts */
	size_t osize;				/* Size of overflow area */
};

struct hash_ops {
    int     (*insert)(hash_t, void *, void *);
    int     (*delete)(hash_t, void *);
    int     (*replace)(hash_t, void *, void *);
    void *  (*lookup)(hash_t, void *);
    int     (*destroy)(hash_t);
    void ** (*getkeys)(hash_t);
    void ** (*getvalues)(hash_t);
};

/*****************************************************************************/

/* Helper functions */
static uint32_t gethash(hash_t, void *);

/* Set of private functions and structs for each hash table type operations */

/* Chain hash */
static int ch_insert(hash_t, void *, void *);
static int ch_delete(hash_t, void *);
static int ch_replace(hash_t, void *, void *);
static void *ch_lookup(hash_t, void *);
static int ch_destroy(hash_t);
static void **ch_getkeys(hash_t);
static void **ch_getvalues(hash_t);

struct hash_ops ch_ops={
	.insert=ch_insert,
	.delete=ch_delete,
	.replace=ch_replace,
	.lookup=ch_lookup,
	.destroy=ch_destroy,
	.getkeys=ch_getkeys,
	.getvalues=ch_getvalues
};

/* Open Address Hash */
static int oa_insert(hash_t, void *, void *);
static int oa_delete(hash_t, void *);
static void *oa_lookup(hash_t, void *);
static int oa_replace(hash_t, void *, void *);
static int oa_destroy(hash_t);
static void **oa_getkeys(hash_t);
static void **oa_getvalues(hash_t);

struct hash_ops oa_ops={
	.insert=oa_insert,
	.delete=oa_delete,
	.replace=oa_replace,
	.lookup=oa_lookup,
	.destroy=oa_destroy,
	.getkeys=oa_getkeys,
	.getvalues=oa_getvalues
};


/* Hash with overflow area */

static int ov_insert(hash_t, void *, void *);
static int ov_delete(hash_t, void *);
static void *ov_lookup(hash_t, void *);
static int ov_replace(hash_t, void *, void *);
static int ov_destroy(hash_t);
static void **ov_getkeys(hash_t);
static void **ov_getvalues(hash_t);

struct hash_ops ov_ops={
	.insert=ov_insert,
	.delete=ov_delete,
	.replace=ov_replace,
	.lookup=ov_lookup,
	.destroy=ov_destroy,
	.getkeys=ov_getkeys,
	.getvalues=ov_getvalues	
};



/* Set of wrapper functions that call the right function for every
 * hash table type, except hashit_create that must create and allocate
 * memory for each hash table type */

hash_t
hashit_create(uint32_t sizehint, size_t keysize, uint32_t (*hfunc)(unsigned char *, unsigned long),
				int(*cfunc)(void *,void *), unsigned int flags)
{
	hash_t htable;
	uint32_t size=0; /* Table size */
	int i=1;

	/* Take the size hint and round it to the next higher power of two */
	while (size < sizehint ) {
		size= 1<<i++;
		if (size==0) { size= 1<< (i-2); break; }
	}

	if (cfunc==NULL) {
		errno=EINVAL;
		return NULL;
	}

	/* Create hash table */
	htable=malloc(sizeof(struct shash_t));
	if (!htable) 
		{ errno=ENOMEM; return NULL; }

	/* And create structs for each hash table type */
		
	switch(flags) {
		case CHAIN_H:
			htable->h_ops=&ch_ops;
			htable->cm.chtable=malloc(size*sizeof(struct elem *));
			if (!htable->cm.chtable) {
				free(htable); errno=ENOMEM; return NULL;
			}

			memset(htable->cm.chtable, '\0', size*sizeof(struct elem *));
			break;

		case OADDRESS_H:
			htable->h_ops=&oa_ops;
			htable->cm.oatable=malloc(size*sizeof(struct oaelem));
			if (!htable->cm.oatable) {
				free(htable); errno=ENOMEM; return NULL;
			}

			memset(htable->cm.oatable, '\0', size*sizeof(struct oaelem));
			break;

		case OVERFLOW_H:
			htable->h_ops=&ov_ops;
			htable->cm.ov=malloc(sizeof(struct ov));
			if (!htable->cm.ov) {
				free(htable);
				errno=ENOMEM;
				return NULL;
			}
			htable->cm.ov->ovtable=malloc(size*sizeof(struct elem));
			if (!htable->cm.ov->ovtable) {
				free(htable->cm.ov);
				free(htable);
				errno=ENOMEM;
				return NULL;
			}
			htable->cm.ov->osize=size/4;
			htable->cm.ov->ovarea=malloc( (htable->cm.ov->osize) * sizeof(struct elem));
			if (!htable->cm.ov->ovarea) {
				free(htable->cm.ov->ovtable);
				free(htable->cm.ov);
				free(htable);
				errno=ENOMEM;
				return NULL;
			}

			htable->cm.ov->cachedidx=0;

			memset(htable->cm.ov->ovtable, '\0', size*sizeof(struct elem));
			memset(htable->cm.ov->ovarea, '\0', (size/4)*sizeof(struct elem));
			break;    

		default:
			//	SAY("Unknown type");
				free(htable);
				errno=EINVAL;
				return NULL;
	}


	/* Initialize hash table common fields */
	htable->tsize=size;
	htable->ksize=keysize;
	htable->nelems=0;

	if (hfunc==NULL) 
		htable->hash_fn=BOB_HASH;
	else 
		htable->hash_fn=hfunc;

	htable->compare_fn=cfunc;

	return htable;
}



int 
hashit_insert(hash_t htable, void *key, void *data)
{
	assert(htable);
	assert(key);
	assert(data);

	return htable->h_ops->insert(htable,key,data);
}
    
    
int
hashit_delete(hash_t htable, void *key) 
{
	assert(htable);
	assert(key); 

	return htable->h_ops->delete(htable, key);
}


int
hashit_replace(hash_t htable, void *key, void *newdata)
{
	assert(htable);
	assert(key);
	assert(newdata);

	return htable->h_ops->replace(htable, key, newdata);
}


void *
hashit_lookup(hash_t htable, void *key)
{
	assert(htable);
	assert(key);

	return htable->h_ops->lookup(htable, key);
}
    

int
hashit_destroy(hash_t htable)
{
	int ret;
	assert(htable); 

	ret=htable->h_ops->destroy(htable);

	free(htable);
	return ret;
}


void **
hashit_getkeys(hash_t htable)
{
	assert(htable);

	return htable->h_ops->getkeys(htable);
}


void **hashit_getvalues(hash_t htable)
{
    assert(htable);

    return htable->h_ops->getvalues(htable);
}
 

/*****************************************************************************/

/* Key and data memory MUST be previously reserved by the application,
 * so the hash table functions only need to insert in the hash table
 * pointers to both of them */
static int
ch_insert(hash_t htable, void *key, void *data) 
{
	uint32_t idx;
	struct elem* cursor;
	struct elem* oneelem;

	idx=gethash(htable, key);   

	oneelem=malloc(sizeof(struct elem));
	if (!oneelem) {
		errno=ENOMEM;
		return -1;
	}

	oneelem->key=key;
	oneelem->data=data;
	oneelem->next=NULL;

	/* No collision ;), first element in this bucket */
	if (htable->cm.chtable[idx]==NULL) 
		htable->cm.chtable[idx]=oneelem;
	/* Collision, insert at the end of the chain */
	else { 
		cursor=htable->cm.chtable[idx];
		while (1) {
			if ( htable->compare_fn(cursor->key,oneelem->key) == 0 ) {
				/* Oops, key is already inserted in the table, insert fails */
				errno=EINVAL;
				free(oneelem);
				return -1;
			}
			if (cursor->next==NULL) break;
				cursor=cursor->next;
		} 

		/* Insert element at the end of the chain */
		cursor->next=oneelem;
	}

	htable->nelems++;
	return 0;	
}


static void *
ch_lookup(hash_t htable, void *key) 
{
	uint32_t idx;
	struct elem *cursor;

	idx=gethash(htable, key);   

	cursor=htable->cm.chtable[idx];

	/* Search thru the chain for the asked key */
	while ( cursor!=NULL ) {
		if ( htable->compare_fn(cursor->key, key)==0 ) 
			return cursor->data;	
		cursor=cursor->next;
	}

	errno=EFAULT;
	return NULL;
}

/* Data associated to this key MUST be freed by the caller */
/* TODO: Implement callbacks so ch_delete can free this data */
static int
ch_delete(hash_t htable, void *key) 
{
	uint32_t idx;
	struct elem *cursor;   /* Cursor for the linked list */
	struct elem *tmp;      /* Pointer to the element to be deleted*/

	idx=gethash(htable, key);   

	if (!htable->cm.chtable[idx]) {
		errno=EFAULT;
		return -1;
	}

	/* Delete asked element */
	/* Element to delete is the first in the chain */
	if ( htable->compare_fn(htable->cm.chtable[idx]->key,key)==0 ) {
		tmp=htable->cm.chtable[idx];
		htable->cm.chtable[idx]=tmp->next;
		free(tmp);
		htable->nelems--;
		return 0;
	}
	/* Search thru the chain for the element */
	else {
		cursor=htable->cm.chtable[idx];
		while ( cursor->next!=NULL ) {
			if ( htable->compare_fn(cursor->next->key, key)==0 ) {
				tmp=cursor->next;
				cursor->next=tmp->next;
				free(tmp);
				htable->nelems--;
				return 0;
			}
			cursor=cursor->next;
		}
	}

	errno=EFAULT;
	return -1;
}


/* Old data associated to this key MUST be freed by the caller */
/* TODO: Implement callbacks so ch_delete can free this data */
static int
ch_replace(hash_t htable, void *key, void *newdata)
{
	uint32_t idx;
	struct elem *cursor;

	idx=gethash(htable, key);

	cursor=htable->cm.chtable[idx];

	/* Search thru the chain for the asked key */
	while ( cursor!=NULL ) {
		if ( htable->compare_fn(cursor->key, key)==0 ) {
			cursor->data=newdata;
			return 0;
		}
		cursor=cursor->next;
	}

	errno=EFAULT;
	return -1;
}


static int
ch_destroy(hash_t htable) 
{
	uint32_t idx;
	struct elem *cursor;

	for (idx=0; idx < htable->tsize; idx++) {	
		cursor=htable->cm.chtable[idx];

		while (cursor!=NULL) {
			struct elem *tmp_cursor=cursor;

			cursor=cursor->next;
			free (tmp_cursor);
		}
	}
	free(htable->cm.chtable);
	return 0;
}

/* Return a NULL terminated string of pointers to all hash table keys */
static void **
ch_getkeys(hash_t htable)
{
	uint32_t idx;
	struct elem *cursor;
	void **keys;
	uint32_t kidx; 

	keys=malloc((htable->nelems+1) *sizeof(void *));
	if (!keys) {
		errno=ENOMEM;
		return NULL;
	}
	keys[htable->nelems] = NULL;
	kidx=0;

	for (idx=0; idx < htable->tsize; idx++) {	

		cursor=htable->cm.chtable[idx];
		while (cursor!=NULL) {
			//SAY("Element %d in bucket %d, key %s value %s", kidx, idx, cursor->key, cursor->data);
			keys[kidx]=cursor->key;
			kidx++;
		
			cursor=cursor->next;
		}
	}

	return keys;
}

/* Return a NULL terminated string of pointers to all hash table values */
static void **ch_getvalues(hash_t htable)
{
    uint32_t idx;
    struct elem *cursor;
    void **values;
    uint32_t vidx; 

    values=malloc((htable->nelems+1) *sizeof(void *));
    if (!values) {
	errno=ENOMEM;
	return NULL;
    }
    values[htable->nelems] = NULL;
    vidx=0;

    for (idx=0; idx < htable->tsize; idx++) {	

	cursor=htable->cm.chtable[idx];
	while (cursor!=NULL) {
	    //SAY("Element %d in bucket %d, key %s value %s", kidx, idx, cursor->key, cursor->data);
	    values[vidx]=cursor->data;
	    vidx++;
	    
	    cursor=cursor->next;
	}
    }
   
    return values;
}

/*****************************************************************************/

static int
oa_insert(hash_t htable, void *key, void *data)
{
	uint32_t pos;
	uint32_t idx;

	pos=gethash(htable, key);   

	idx=pos;
	/* Use linear probing by now. TODO: Add more probing types */
	while ( htable->cm.oatable[idx].key!=NULL ) { /* This slot is occupied */
		if ( htable->compare_fn(htable->cm.oatable[idx].key, key)==0 ) {
			errno=EINVAL;
			return -1;
		}
		idx++;
		if ( idx == htable->tsize ) idx=0;
		if ( idx==pos ) {
			errno=ENOSPC;
			return -1;
		}
	}

	htable->cm.oatable[idx].key=key;
	htable->cm.oatable[idx].data=data;

	htable->nelems++;
	return 0;
}


static int
oa_delete(hash_t htable, void *key)
{
	uint32_t pos;
	uint32_t idx;

	pos=gethash(htable, key);   

	idx=pos;
	while (htable->cm.oatable[idx].key!=NULL) {
		if ( htable->compare_fn(htable->cm.oatable[idx].key, key)==0 ) {
			htable->cm.oatable[idx].key=NULL;
			htable->cm.oatable[idx].data=NULL;
			htable->nelems--;

			while (1) {
				void *tmp_key;
				void *tmp_data;

				idx++;
				if (idx == htable->tsize) idx=0;
				if (idx==pos) break;
				if (!htable->cm.oatable[idx].key) break;

				tmp_key=htable->cm.oatable[idx].key;
				tmp_data=htable->cm.oatable[idx].data;

				htable->cm.oatable[idx].key=NULL;
				htable->cm.oatable[idx].data=NULL;
				htable->nelems--;
				oa_insert(htable, tmp_key, tmp_data);
			}
			return 0;
		}
		idx++;
		if (idx == htable->tsize) idx=0;    /* Wrap around */
		if (idx==pos) break;   /* Been there, seen that ;) */
	}

	errno=EFAULT;
	return -1;
}


static void *
oa_lookup(hash_t htable, void *key)
{
	uint32_t pos;
	uint32_t idx;

	pos=gethash(htable, key);   

	idx=pos;    
	while (htable->cm.oatable[idx].key!=NULL) {
		if (htable->compare_fn(htable->cm.oatable[idx].key, key)==0 ) 
			return htable->cm.oatable[idx].data;
		idx++;
		if (idx == htable->tsize) idx=0;    /* Wrap around */
		if (idx==pos) break;   /* Been there, seen that ;) */
	}

	errno=EFAULT;
	return NULL;
}


static int
oa_replace(hash_t htable, void *key, void *newdata)
{
	uint32_t pos;
	uint32_t idx;

	pos=gethash(htable, key);   

	idx=pos;
	while (htable->cm.oatable[idx].key!=NULL) {
		if ( htable->compare_fn(htable->cm.oatable[idx].key, key)==0 ) {
			htable->cm.oatable[idx].data=newdata;
			return 0;
		}
		idx++;
		if (idx == htable->tsize) idx=0;    /* Wrap around */
		if (idx==pos) break;   /* Been there, seen that ;) */
	}

	errno=EFAULT;
	return -1;
}


static int
oa_destroy(hash_t htable)
{
	free(htable->cm.oatable);

	return 0;
}


/* Return a NULL terminated string of pointers to all hash table keys */
static void **
oa_getkeys(hash_t htable)
{
	uint32_t	idx;
	void	**keys;
	uint32_t	kidx; 

	keys = malloc ((htable->nelems + 1) * sizeof (void *));

	if (keys==NULL) {
		errno=ENOMEM;
		return NULL;
	}
	keys[htable->nelems] = NULL;
	kidx = 0;

	for (idx = 0; idx < htable->tsize; idx++) {
		if (htable->cm.oatable[idx].key!=NULL)
			keys[kidx++] = htable->cm.oatable[idx].key;
	}
	return keys;
}

/* Return a NULL terminated string of pointers to all hash table values */
static void **oa_getvalues(hash_t htable)
{
    uint32_t	idx;
    void	**values;
    uint32_t	vidx; 

    values = malloc ((htable->nelems + 1) * sizeof (void *));

    if (values==NULL) {
	errno=ENOMEM;
	return NULL;
    }
    values[htable->nelems] = NULL;
    vidx = 0;

    for (idx = 0; idx < htable->tsize; idx++) {
	if (htable->cm.oatable[idx].key!=NULL)
	    values[vidx++] = htable->cm.oatable[idx].data;
    }
    return values;
}

/*****************************************************************************/

static int
ov_insert(hash_t htable, void *key, void *data)
{
	uint32_t idx;
	uint32_t tidx;
	struct elem *cursor;
	unsigned int i=0;

	idx=gethash(htable, key);   
	tidx=idx;

	/* No collision ;), insert element in the table */
	if (htable->cm.ov->ovtable[idx].key==NULL) {
		htable->cm.ov->ovtable[idx].key=key;
		htable->cm.ov->ovtable[idx].data=data;
		htable->cm.ov->ovtable[idx].next=NULL;
		htable->nelems++;
		return 0;
	}

	/* Collision, look for a free slot in the overflow area, if the
	 * the key is already inserted return EINVAL */

	cursor=&(htable->cm.ov->ovtable[idx]);

	while (1) {
		if ( htable->compare_fn(cursor->key,key)==0 ) {
			errno=EINVAL;
			return -1;
		}
		if (cursor->next==NULL) break;
		cursor=cursor->next;
	}

	/* Then insert the element in the index position previously cached or
	 * if nothing is cached, look for a free slot in the overflow area */
	if (htable->cm.ov->cachedidx != UINT32_MAX ) {
		i=htable->cm.ov->cachedidx;
		if (i < htable->cm.ov->osize-1) 
			htable->cm.ov->cachedidx++;
		else
			htable->cm.ov->cachedidx=UINT32_MAX;
	} else {
		i=0;
		while ( (i < htable->cm.ov->osize) && (htable->cm.ov->ovarea[i].key!=NULL) )
			i++;
	}

	/* Insert the element */    
	if (i < htable->cm.ov->osize) {
		htable->cm.ov->ovarea[i].key=key;
		htable->cm.ov->ovarea[i].data=data;
		htable->cm.ov->ovarea[i].next=NULL;
		cursor->next=&(htable->cm.ov->ovarea[i]);
		htable->nelems++;
		return 0;
	}

	/* Overflow area is full, make it bigger to put more shit inside ;)) */

	i=htable->cm.ov->osize;

	if ( i*2 < htable->tsize) {
		struct elem *oldarea=htable->cm.ov->ovarea;

		htable->cm.ov->ovarea=realloc(oldarea, i*2*sizeof (struct elem));

		if (htable->cm.ov->ovarea != oldarea) {
			if (htable->cm.ov->ovarea==NULL) {
				/* realloc failed, put back old address and return */
				htable->cm.ov->ovarea=oldarea;
				errno=ENOSPC;
				return -1;
			}
			/* Overflow area has been assigned a different memory region, and
			   thus all pointers into it has to be recalculated. */
			struct elem *rcursor;
			struct elem *newarea=htable->cm.ov->ovarea;

			for (idx=0; idx < htable->tsize; idx++) {
				rcursor=&htable->cm.ov->ovtable[idx];
				while (rcursor->next!=NULL) {
					rcursor->next=(rcursor->next-oldarea)+newarea;
					rcursor=rcursor->next;
				}
			}
			if (cursor!=&(htable->cm.ov->ovtable[tidx]))
				cursor=(cursor-oldarea)+newarea;
		}
		htable->cm.ov->osize=i*2;
		htable->cm.ov->ovarea[i].key=key;
		htable->cm.ov->ovarea[i].data=data;
		htable->cm.ov->ovarea[i].next=NULL;
		cursor->next=&(htable->cm.ov->ovarea[i]);
		htable->cm.ov->cachedidx=i+1;
		htable->nelems++;
		return 0;
	}   
	
	errno=ENOSPC;
	return -1;	
}
    
    
    
static int
ov_delete(hash_t htable, void *key)
{
	uint32_t idx;
	struct elem *cursor;

	idx=gethash(htable, key);   

	cursor=&(htable->cm.ov->ovtable[idx]);

	if (cursor->key==NULL) {
		errno=EFAULT;
		return -1;
	}
	
	while (cursor!=NULL) {
		if ( htable->compare_fn(cursor->key,key)==0 ) {
			cursor->key=NULL;
			cursor->data=NULL;
			/* Take out the next element from the overflow area and put it in
			 * the hash table, to fill the empty slot */
			if (cursor->next) {
				struct elem *tmp=cursor->next;
				cursor->key=tmp->key;
				cursor->data=tmp->data;
				cursor->next=tmp->next;
				tmp->key=NULL;
				tmp->data=NULL;
			}
			htable->nelems--;
			return 0;
		}
		cursor=cursor->next;
	}

	errno=EFAULT;
	return -1;

}

    
static void *
ov_lookup(hash_t htable, void *key)
{
	uint32_t idx;
	struct elem *cursor;

	idx=gethash(htable, key);   

	cursor=&(htable->cm.ov->ovtable[idx]);

	if (cursor->key==NULL) {
		errno=EFAULT;
		return NULL;
	}
	
	while (cursor!=NULL) {
		if (htable->compare_fn(cursor->key, key)==0 ) 
			return cursor->data;
		cursor=cursor->next;
	}
		
	errno=EFAULT;
	return NULL;
}


static int
ov_replace(hash_t htable, void *key, void *newdata)
{
	uint32_t idx;
	struct elem *cursor;

	idx=gethash(htable, key);   

	cursor=&(htable->cm.ov->ovtable[idx]);

	if (cursor->key==NULL) {
		errno=EFAULT;
		return -1;
	}
	
	while (cursor!=NULL) {
		if (htable->compare_fn(cursor->key, key)==0 ) { 
			cursor->data=newdata;
			return 0;
		}
		cursor=cursor->next;
	}
		
	errno=EFAULT;
	return -1;
}

    
static int
ov_destroy(hash_t htable)
{
	free(htable->cm.ov->ovtable);
	free(htable->cm.ov->ovarea);
	free(htable->cm.ov);

	return 0;
}


/* Return a NULL terminated string of pointers to all hash table keys */
static void **
ov_getkeys(hash_t htable)
{
	uint32_t idx;
	uint32_t kidx; 
	struct elem *cursor;
	void **keys;

	keys=malloc((htable->nelems+1) *sizeof(void *));
	if (!keys) {
		errno=ENOMEM;
		return NULL;
	}
	keys[htable->nelems] = NULL;
	kidx=0;

	for (idx=0; idx < htable->tsize; idx++) {
		cursor=&htable->cm.ov->ovtable[idx];
		if (cursor->key==NULL) continue;
		while (cursor!=NULL) {
			//SAY("Element %d in bucket %d, key %s value %s", kidx, idx, cursor->key, cursor->data);
			keys[kidx]=cursor->key;
			kidx++;
			cursor=cursor->next;
		}
	}

	return keys;
}

/* Return a NULL terminated string of pointers to all hash table values */
static void **ov_getvalues(hash_t htable)
{
    uint32_t idx;
    uint32_t vidx; 
    struct elem *cursor;
    void **values;

    values=malloc((htable->nelems+1) *sizeof(void *));
    if (!values) {
	errno=ENOMEM;
	return NULL;
    }
    values[htable->nelems] = NULL;
    vidx=0;

    for (idx=0; idx < htable->tsize; idx++) {
	cursor=&htable->cm.ov->ovtable[idx];
	if (cursor->key==NULL) continue;
	while (cursor!=NULL) {
	    //SAY("Element %d in bucket %d, key %s value %s", kidx, idx, cursor->key, cursor->data);
	    values[vidx]=cursor->data;
	    vidx++;
	    cursor=cursor->next;
	}
    }
   
    return values;
}


/* Accesors ******************************************************************/
inline size_t
hashit_tablesize(hash_t htable)
{
	return htable->tsize;
}


inline size_t
hashit_size(hash_t htable)
{
	return htable->nelems;
}

 
/* Misc functions ************************************************************/
static uint32_t
gethash(hash_t htable, void *key) 
{
	size_t len;

	if (htable->ksize==0)
		len=strlen(key);
	else
		len=htable->ksize;

	/* Hash the key and get the meaningful bits for our table */
	return ( (htable->hash_fn(key, len)) & (htable->tsize-1) );    
}
