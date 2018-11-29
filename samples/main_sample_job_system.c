#include "jobsystem/jobsystem.h"

#include "c11threads.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    job_manager_t *jm = create_job_manager(5, 128, 32*1024);
    thrd_sleep(&(struct timespec){.tv_sec=5}, NULL); // sleep 5 sec
    stop_job_manager(jm);
    destroy_job_manager(&jm);
    return 0;
}
