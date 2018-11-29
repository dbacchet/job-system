#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t job_id_t;
typedef void (*job_function_ptr)(void*);

typedef struct job_t_ {
    job_id_t id;          ///< job id
    job_function_ptr fcn; ///< job function
    void *data;           ///< job data
    void *counter;        ///< pointer to an atomic counter for job synchronization
} job_t;

#ifdef __cplusplus
}
#endif
