#include "jobsystem/job_queue.h"

#include "c11threads.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// node of the job queue
typedef struct job_queue_node_t_ {
    job_t job;
    struct job_queue_node_t_* volatile next;
} job_queue_node_t;

// job queue
struct job_queue_t_ {
    job_queue_node_t* volatile head;
    job_queue_node_t* volatile tail;
    mtx_t mtx;
};

job_queue_t job_queue_create() {
    struct job_queue_t_ *q = (struct job_queue_t_*)malloc(sizeof(struct job_queue_t_));
    memset(q,0x0,sizeof(struct job_queue_t_));
    mtx_init(&q->mtx, mtx_plain);
    return q;
}

bool job_queue_destroy(job_queue_t *q_) {
    if (!q_ || !(*q_)) {
        return false;
    }
    struct job_queue_t_ *q = *q_;
    mtx_lock(&q->mtx);
    while(q->tail) {
        job_queue_node_t *n = q->tail;
        q->tail = q->tail->next;
        free(n);
    }
    mtx_unlock(&q->mtx);
    mtx_destroy(&q->mtx);
    free(q);
    *q_ = NULL;
    return true;
}

bool job_queue_empty(const job_queue_t q) {
    return !q || q->head == NULL;
}

size_t job_queue_size(const job_queue_t q) {
    if (!q) {
        return 0;
    }
    mtx_lock(&q->mtx);
    int count = 0;
    job_queue_node_t *n = q->tail;
    while (n) {
        count++;
        n = n->next;
    }
    mtx_unlock(&q->mtx);
    return count;
}

bool job_queue_push(job_queue_t q, job_t job) {
    if (!q) {
        return false;
    }
    job_queue_node_t *n = (job_queue_node_t*)malloc(sizeof(job_queue_node_t));
    n->job = job;
    n->next = NULL;
    mtx_lock(&q->mtx);
    // update head
    if (q->head) {
        q->head->next = n;
    }
    q->head = n;
    // set tail in case of empty queue
    if (!q->tail) {
        q->tail = n;
    }
    mtx_unlock(&q->mtx);
    return true;
}

bool job_queue_pop(job_queue_t q, job_t *job) {
    if (!q) {
        return false;
    }
    mtx_lock(&q->mtx);
    if (!q->tail) {
        mtx_unlock(&q->mtx);
        return false;
    }
    *job = q->tail->job;
    // update tail and free memory
    job_queue_node_t *tail = q->tail;
    q->tail = tail->next;
    free(tail);
    // update head if the queue is empty
    if (!q->tail) {
        q->head = NULL;
    }
    mtx_unlock(&q->mtx);
    return true;
}

