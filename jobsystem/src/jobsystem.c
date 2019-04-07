#include "jobsystem/jobsystem.h"
#include "fcontext/fcontext.h"

#include "c11threads.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdatomic.h>

struct atomic_counter_t {
    atomic_int counter;
};
typedef struct atomic_counter_t* atomic_counter_handle;

// the job_ manager_t struct contains all the data structures needed to schedule and synchronize jobs
struct job_manager_t {
    thrd_t *threads;
    size_t num_threads;
    atomic_bool stop_threads;
};
typedef struct job_manager_t* job_manager_handle;

// /////////////////////////////////// //
// fiber data structures and functions //
// /////////////////////////////////// //

struct fiber_function_data_t {
    job_manager_handle jm; // job manager
};

// function executed by the fibers: will keep fetching and executing jobs
void fiber_function(fcontext_transfer_t t) {
    struct fiber_function_data_t *fiber_data = (struct fiber_function_data_t*)t.data;
    job_manager_handle jm = fiber_data->jm;
    while (jm && !jm->stop_threads) {
        printf("executing fiber function on thread %llx\n", (uint64_t)thrd_current());
        thrd_sleep(&(struct timespec){.tv_sec=1}, NULL);
    }
    // back to the calling context
    jump_fcontext(t.ctx, t.data);
}

// //////////////////////////////////// //
// thread data structures and functions //
// //////////////////////////////////// //

struct thread_function_data_t {
    job_manager_handle jm; // job manager
};

// the thread function just does some housekeeping and then switches to the context of the fiber. 
// The job system works completely inside the fibers' context
int thread_function(void *data) {
    struct thread_function_data_t *thread_data = (struct thread_function_data_t*)data;

    printf("executing thread function on thread %llx\n", (uint64_t)thrd_current());
    // switch context
    fcontext_stack_t s1 = create_fcontext_stack(32 * 1024);
    fcontext_t ctx1 = make_fcontext(s1.sptr, s1.ssize, fiber_function);
    struct fiber_function_data_t fiber_data = {thread_data->jm};
    jump_fcontext(ctx1, (void*)&fiber_data);

    // back to the original thread context
    printf("back to thread function on thread %llx\n", (uint64_t)thrd_current());
    destroy_fcontext_stack(&s1);
    return 0;
}


// ////////// //
// job system //
// ////////// //

job_manager_handle create_job_manager(uint32_t num_worker_threads, uint32_t num_fibers, uint32_t fiber_stack_size) {
    job_manager_handle jm = (struct job_manager_t*)malloc(sizeof(struct job_manager_t));
    jm->threads = (thrd_t*)malloc(num_worker_threads*sizeof(thrd_t));
    jm->num_threads = num_worker_threads;
    jm->stop_threads = false;
    // create and start threads
    for (int i=0; i<jm->num_threads; i++) {
        struct thread_function_data_t *data = (struct thread_function_data_t*)malloc(sizeof(struct thread_function_data_t));
        data->jm = jm;
        thrd_create(jm->threads+i, thread_function, data);
    }
    return jm;
}

void stop_job_manager(job_manager_handle jm) {
    jm->stop_threads = true;
    for (int i=0; i<jm->num_threads; i++) {
        thrd_join(jm->threads[i], NULL);
    }
}

void destroy_job_manager(job_manager_handle jm) {
    // stop threads in case they're still running
    if (!jm->stop_threads) {
        stop_job_manager(jm);
    }
    free(jm);
    jm = NULL;
}

