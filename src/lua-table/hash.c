#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

static hcode_t hash_func_int64(const htype_t type, const hvalue_t value);
static hcode_t hash_func_string(const htype_t type, const hvalue_t value);

hcode_t hash_code(const htype_t type, const hvalue_t value) {
  switch (type) {
    case H_INT64:
    case H_UINT64:
      return hash_func_int64(type, value);

    case H_STRING:
      return hash_func_string(type, value);

    case H_VOID:
      return (hcode_t)(size_t)value;

    default:
      return (hcode_t)value;
  }
}

int32_t hash_equal(const htype_t type, const hvalue_t a, const hvalue_t b) {
  switch (type) {
    case H_STRING: {
      const char *sa = (const char *)(size_t)a;
      const char *sb = (const char *)(size_t)b;
      if ((sa == NULL || sb == NULL) && sa != sb) {
        return 0;
      } else{
        return strcmp(sa, sb) == 0;
      }
    }

    default:
      return a == b;
  }
}

static hcode_t hash_func_int64(const htype_t type, const hvalue_t value) {
  hcode_t code[sizeof(uint64_t) / sizeof(hcode_t)];
  uint64_t i, n = (uint64_t)value;
  assert(sizeof(code) <= sizeof(n));
  memcpy(code, &n, sizeof(code));
  for (i = 1; i < sizeof(uint64_t) / sizeof(hcode_t); ++i) {
    code[0] += code[i];
  }
  return code[0];
}

static hcode_t hash_func_string(const htype_t type, const hvalue_t value) {
  const char *s = (const char *)(size_t)value;
  hcode_t hash = (hcode_t)*s;
  if (hash) {
    while (*(++s)) {
      hash = hash ^ ((hash << 5) + (hash >> 2) + (unsigned char)*s);
    }
  }
  return hash;
}
