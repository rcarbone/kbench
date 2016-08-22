#ifndef LH3_RUNLIB_H_
#define LH3_RUNLIB_H_

#include <stdlib.h>

#define RUN_ERR_WRONG_OS	1
#define RUN_ERR_MISSING_INFO	2
#define RUN_ERR_PROC_FINISHED	3


/* static system information */
typedef struct
{
  size_t mem_total;
  size_t page_size;
  size_t swap_total;

} RunSysStatic;


/* dynamic system information */
typedef struct
{
  double wall_clock;
  size_t mem_free;
  size_t mem_available;

} RunSysDyn;


/* dynamic process information */
typedef struct
{
  size_t rss, vsize;
  double utime, stime;

} RunProcDyn;


int run_get_static_sys_info (RunSysStatic * rss);
int run_get_dynamic_sys_info (RunSysDyn * rsd);
int run_get_dynamic_proc_info (pid_t pid, RunProcDyn * rpd);

#endif /* ! LH3_RUNLIB_H_ */
