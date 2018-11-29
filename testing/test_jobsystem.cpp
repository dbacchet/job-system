#include "jobsystem/jobsystem.h"

#include "catch2/catch.hpp"

TEST_CASE("jobsystem creation", "[jobsystem]") {
    create_job_manager(4, 20, 512);
    // ConcurrentQueue<int> q;
    // ASSERT_EQ(q.size(),0);
    // q.push(1);
    // ASSERT_EQ(q.size(),1);
}

TEST_CASE("jobsystem run", "[jobsystem]") {
    create_job_manager(4, 10, 1024*1024);
    // ConcurrentQueue<int> q;
    // ASSERT_EQ(q.size(),0);
    // q.push(1);
    // ASSERT_EQ(q.size(),1);
}

