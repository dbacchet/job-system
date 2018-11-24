# select fcontext (fibers/coroutines) asm files for the current OS
if (APPLE)
    set(CPU_ARCH "combined")
    set(ASM_EXT "all_macho_gas.S")
elseif (UNIX)
    # PC (x86/x64)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(CPU_ARCH "x86_64")
    else()
        set(CPU_ARCH "i386")
    endif()
    set(ASM_EXT "sysv_elf_gas.S")  # Linux/Unix
endif()
set(ASM_SOURCES "asm/make_${CPU_ARCH}_${ASM_EXT}"
                "asm/jump_${CPU_ARCH}_${ASM_EXT}"
                "asm/ontop_${CPU_ARCH}_${ASM_EXT}")

# jobsystem static library
set(C_HEADERS include/fcontext/fcontext.h
              include/jobsystem/job.h
              include/jobsystem/job_queue.h
              include/jobsystem/jobsystem.h)
set(C_SOURCES src/fcontext.c 
              src/job_queue.c
              src/jobsystem.c)
add_library(jobsystem STATIC ${C_HEADERS}
                             ${C_SOURCES}
                             ${ASM_SOURCES})
target_include_directories(jobsystem PUBLIC include)
target_link_libraries(jobsystem PRIVATE c11threads)
