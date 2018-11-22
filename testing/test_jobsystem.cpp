#include <iostream>
#include <thread>

#include "gtest/gtest.h"

#include "jobsystem/jobsystem.h"

// namespace {
//     void add_elements(ConcurrentQueue<int> *q, int base) {
//         for (auto i=0; i<100; i++)
//             q->push(base+i);
//     }
//     int get_one(ConcurrentQueue<int> *q) {
//         return q->pop();
//     }
//     void pop_elements(ConcurrentQueue<int> *q, int num) {
//         for (auto i=0; i<num; i++)
//             q->pop();
//     }
// }

TEST(JobSystem, Creation) {
    create_job_system();
    // ConcurrentQueue<int> q;
    // ASSERT_EQ(q.size(),0);
    // q.push(1);
    // ASSERT_EQ(q.size(),1);
}

