#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#ifdef __cplusplus
extern "C" {
#endif

int udb_benchmark (int argc, char * argv [], int (* func_int) (int, const unsigned *), int (* func_str) (int, char * const *));

#ifdef __cplusplus
}
#endif

#endif /* ! _BENCHMARK_H_ */
