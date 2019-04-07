#include "jobsystem/jobsystem.h"

#include "catch2/catch.hpp"

TEST_CASE("jobsystem creation", "[jobsystem]") {
    auto jm = create_job_manager(4, 20, 512);
    REQUIRE(jm != NULL);
    stop_job_manager(jm);
    destroy_job_manager(&jm);
    REQUIRE(jm == NULL);
}

TEST_CASE("jobsystem run", "[jobsystem]") {
    auto jm = create_job_manager(4, 10, 1024*1024);
    // destroy withouth stopping before (will stop automatically)
    REQUIRE(jm != NULL);
    destroy_job_manager(&jm);
    REQUIRE(jm == NULL);
}

