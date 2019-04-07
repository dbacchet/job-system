#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "job.h"

typedef struct atomic_counter_t* atomic_counter_handle;
typedef struct job_manager_t* job_manager_handle;

job_manager_handle create_job_manager(uint32_t num_worker_threads, uint32_t num_fibers, uint32_t fiber_stack_size);
void destroy_job_manager(job_manager_handle jm);

void run_jobs(job_manager_handle jm, job_t *jobs, uint32_t num_jobs, atomic_counter_handle counter);
void wait_for_counter(job_manager_handle jm, atomic_counter_handle counter, uint32_t value);

void stop_job_manager(job_manager_handle job_manager_handle);

#ifdef __cplusplus
}
#endif
