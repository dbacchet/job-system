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
add_library(jobsystem STATIC src/fcontext.c 
                             src/jobsystem.c
                             ${ASM_SOURCES})
target_include_directories(jobsystem PUBLIC include)
