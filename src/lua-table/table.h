#ifndef _H_TABLE_H_
#define _H_TABLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "hash.h"

typedef enum _table_error {
  TABLE_ERROR_NONE = 0,
  TABLE_ERROR_MEMORY,
  TABLE_ERROR_OVERFLOW,
  MAX_TABLE_ERROR
} table_error_t;

typedef struct _table table_t;
typedef struct _table_node table_node_t;

struct _table {
  table_node_t *nodes;
  int32_t nodes_size_log;
  table_node_t *inactive_node;
  htype_t hash_type;
  hash_func_t hash_func;
  hash_equal_func_t hash_equal_func;
  table_error_t error;
};

struct _table_node {
  hvalue_t key;
  hvalue_t value;
  table_node_t *next;
  int8_t active;
};

/**
* Initialize a table object.
*
* @param type Hash type for the table's keys.
* @param fn Hash function. If NULL, hash_code will be used.
* @param eq_fn Key equality function. If NULL, hash_equal will be used.
*/
extern void table_init(table_t * const table, const htype_t type,
                       hash_func_t fn, hash_equal_func_t eq_fn);

/**
* Free the nodes associated with a table.
*/
extern void table_destroy(table_t * const table);

/**
* Return the hash table value for the given key, or NULL if the table does
* not contain the key.
*/
extern hvalue_t table_get(const table_t * const table, const hvalue_t key);

/**
* Set the table key to a value, and return the table node. The table will
* be resized if there isn't enough space. If there is an error, NULL will
* be returned, and table->error will contain the error code.
*/
extern table_node_t *table_set(table_t * const table, const hvalue_t key,
                               const hvalue_t value);

/**
* Return true if the table contains the given key.
*/
int32_t table_contains(const table_t * const table, const hvalue_t key);

/**
* Delete the matching node from the table, if it exists.
*/
extern void table_delete(table_t * const table, const hvalue_t key);

/**
* Return the string version of a table error code.
*/
extern const char *table_error_string(const table_error_t error);

#ifdef __cplusplus
}
#endif

#endif
