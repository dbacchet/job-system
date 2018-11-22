cmake_minimum_required(VERSION 3.12)

project(JobSystem VERSION 0.0.1
                  DESCRIPTION "Minimal Job System based on fibers"
                  LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# generate the compilation database file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()
# recurse subdirectories
add_subdirectory(3rdparty)
add_subdirectory(jobsystem)
add_subdirectory(testing)

