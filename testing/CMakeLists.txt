
add_executable(unit_tests test_jobsystem.cpp
                          test_fcontext.cpp)
target_link_libraries(unit_tests PRIVATE jobsystem
                                         gtest_main)
add_test(unit_tests unit_tests)
