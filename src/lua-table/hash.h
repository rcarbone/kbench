#ifndef _H_HASH_H_
#define _H_HASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum _htype {
  H_NULL,
  H_INT8,
  H_INT16,
  H_INT32,
  H_INT64,
  H_UINT8,
  H_UINT16,
  H_UINT32,
  H_UINT64,
  H_STRING,
  H_VOID
} htype_t;

typedef uint32_t hcode_t;
typedef uint64_t hvalue_t;
typedef hcode_t (*hash_func_t)(const htype_t, const hvalue_t);
typedef int32_t (*hash_equal_func_t)(const htype_t, const hvalue_t, const hvalue_t);

/**
* The default hashing function. Special functions are used for strings and
* 64-bit integers. For other types, the value itself is used.
*/
extern hcode_t hash_code(const htype_t type, const hvalue_t value);

/**
* The default hash key equality function. Strings are compared using strcmp,
* other values are compared directly.
*/
extern int32_t hash_equal(const htype_t type, const hvalue_t a, const hvalue_t b);

#ifdef __cplusplus
}
#endif

#endif
