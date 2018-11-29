add_executable(sample_job_system main_sample_job_system.c
                                 )
target_link_libraries(sample_job_system PRIVATE jobsystem
                                                c11threads)

