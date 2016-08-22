/*
 * R. Carbone on Sun Jul 24 06:18:52 CEST 2016
 *
 */

#include <endian.h>


/* Mandatory define (in order to compile htable.c) */
#if defined(__GNUC__)
#define COLD __attribute__((__cold__))
#endif

/* Optional as found in original compiler.h but not needed to compile htable.c */
#if defined(OPTIONAL)

#define NORETURN                  __attribute__((__noreturn__))
#define PRINTF_FMT(nfmt, narg) 	  __attribute__((format(__printf__, nfmt, narg)))
#define CONST_FUNCTION            __attribute__((__const__))
#define PURE_FUNCTION             __attribute__((__pure__))
#define UNNEEDED                  __attribute__((__unused__))
#define NEEDED                    __attribute__((__used__))
#define UNUSED                    __attribute__((__unused__))
#define IS_COMPILE_CONSTANT(expr) __builtin_constant_p(expr)
#define WARN_UNUSED_RESULT        __attribute__((__warn_unused_result__))

#endif /* OPTIONAL */


/* Mandatory in order to compile hash.c */
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define HAVE_LITTLE_ENDIAN 1

#elif __BYTE_ORDER == __BIG_ENDIAN
#define HAVE_BIG_ENDIAN    1

#endif
