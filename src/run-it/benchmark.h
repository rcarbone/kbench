#ifndef UDB_BENCHMARK_H
#define UDB_BENCHMARK_H

#ifdef __cplusplus
extern "C" {
#endif

  /* Dataset init functions */
  void udb_init_data (unsigned n);
  void grow_init_data (unsigned n);

  unsigned udb_benchmark (int argc, char * argv [],
			  unsigned (* udb_int) (unsigned, unsigned *),
			  unsigned (* udb_str) (unsigned, char **),
			  unsigned (* grow_int) (unsigned, unsigned *),
			  unsigned (* grow_str) (unsigned, char **)
			  );

#ifdef __cplusplus
}
#endif

#endif /* ! _UDB_BENCHMARK_H_ */
