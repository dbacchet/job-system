#include "jobsystem/job.h"
#include "jobsystem/job_queue.h"

#include "catch2/catch.hpp"

#include <stdlib.h>
#include <string.h>


TEST_CASE( "job queue creation", "[job queue]" ) {
    job_queue_t q = job_queue_create();
    REQUIRE(q != nullptr);
    REQUIRE(job_queue_empty(q) == true);
    REQUIRE(job_queue_destroy(NULL) == false);
    REQUIRE(job_queue_destroy(&q) == true);
    REQUIRE(q == nullptr);
}

TEST_CASE( "null job queue", "[job queue]" ) {
    job_queue_t q = nullptr;
    // check APIs with null queue
    REQUIRE(job_queue_destroy(nullptr) == false);
    REQUIRE(job_queue_destroy(&q) == false);
    REQUIRE(job_queue_empty(q) == true);
    REQUIRE(job_queue_size(q) == 0);
    REQUIRE(job_queue_push(q, {1, "uno", NULL, NULL}) == false);
    job_t job;
    REQUIRE(job_queue_pop(q, &job) == false);
}

TEST_CASE( "job queue usage", "[job queue]" ) {
    job_queue_t q = job_queue_create();
    REQUIRE(job_queue_empty(q) == true);
    // add elements
    job_queue_push(q, {1, "uno", NULL, NULL});
    job_queue_push(q, {2, "due", NULL, NULL});
    job_queue_push(q, {3, "tre", NULL, NULL});
    REQUIRE(job_queue_empty(q) == false);
    REQUIRE(job_queue_size(q) == 3);
    // retrieve elements
    job_t j{.id=111};
    REQUIRE(job_queue_pop(q, &j) == true);
    REQUIRE(j.id == 1);
    REQUIRE(strcmp(j.name, "uno") == 0);
    REQUIRE(job_queue_pop(q, &j) == true);
    REQUIRE(j.id == 2);
    REQUIRE(strcmp(j.name, "due") == 0);
    REQUIRE(job_queue_pop(q, &j) == true);
    REQUIRE(j.id == 3);
    REQUIRE(strcmp(j.name, "tre") == 0);
    REQUIRE(job_queue_pop(q, &j) == false);
    job_queue_destroy(&q);
}

TEST_CASE( "job queue destruction", "[job queue]" ) {
    job_queue_t q = job_queue_create();
    REQUIRE(job_queue_empty(q) == true);
    // add elements
    job_queue_push(q, {1, "uno", NULL, NULL});
    job_queue_push(q, {2, "due", NULL, NULL});
    job_queue_push(q, {3, "tre", NULL, NULL});
    REQUIRE(job_queue_empty(q) == false);
    REQUIRE(job_queue_size(q) == 3);
    // cleanup
    REQUIRE(job_queue_destroy(&q) == true);
    REQUIRE(job_queue_empty(q) == true);
}
