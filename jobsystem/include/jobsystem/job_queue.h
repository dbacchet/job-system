#pragma once

#include "job.h"

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// job queue
typedef struct job_queue_t_* job_queue_t;

/// create a job queue
job_queue_t job_queue_create();

/// destroy the queue.
bool job_queue_destroy(job_queue_t *q);

/// check if the queue is empty
bool job_queue_empty(const job_queue_t q);

/// \return size of the queue
size_t job_queue_size(const job_queue_t q);

/// add a job to the queue
/// \return success of the operation
bool job_queue_push(job_queue_t q, job_t job);

/// get a job from the queue
/// \return success of the operation
bool job_queue_pop(job_queue_t q, job_t *job);

#ifdef __cplusplus
}
#endif

