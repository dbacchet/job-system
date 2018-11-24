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
};

job_queue_t job_queue_create() {
    struct job_queue_t_ *q = (struct job_queue_t_*)malloc(sizeof(struct job_queue_t_));
    memset(q,0x0,sizeof(struct job_queue_t_));
    return q;
}

bool job_queue_destroy(job_queue_t *q_) {
    if (!q_ || !(*q_)) {
        return false;
    }
    struct job_queue_t_ *q = *q_;
    while(q->tail) {
        job_queue_node_t *n = q->tail;
        q->tail = q->tail->next;
        free(n);
    }
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
    int count = 0;
    job_queue_node_t *n = q->tail;
    while (n) {
        count++;
        n = n->next;
    }
    return count;
}

bool job_queue_push(job_queue_t q, job_t job) {
    if (!q) {
        return false;
    }
    job_queue_node_t *n = (job_queue_node_t*)malloc(sizeof(job_queue_node_t));
    n->job = job;
    n->next = NULL;
    // update head
    if (q->head) {
        q->head->next = n;
    }
    q->head = n;
    // set tail in case of empty queue
    if (!q->tail) {
        q->tail = n;
    }
    return true;
}

bool job_queue_pop(job_queue_t q, job_t *job) {
    if (!q || !q->tail) {
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
    return true;
}

