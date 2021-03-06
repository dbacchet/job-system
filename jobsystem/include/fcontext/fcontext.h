#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
    typedef void* fcontext_t;

    struct fcontext_transfer_t_
    {
        fcontext_t ctx;
        void* data;
    };
    typedef struct fcontext_transfer_t_ fcontext_transfer_t;

    struct fcontext_stack_t_
    {
        void* sptr;
        size_t ssize;
    };
    typedef struct fcontext_stack_t_ fcontext_stack_t;

    /**
     * Callback definition for context (coroutine)
     */
    typedef void (*pfn_fcontext)(fcontext_transfer_t);

    /**
     * Switches to another context
     * @param to Target context to switch to
     * @param vp Custom user pointer to pass to new context
     */
    fcontext_transfer_t jump_fcontext(fcontext_t const to, void * vp);

    /**
     * Make a new context
     * @param sp Pointer to allocated stack memory
     * @param size Stack memory size
     * @param corofn Callback function for context (coroutine)
     */
    fcontext_t make_fcontext(void * sp, size_t size, pfn_fcontext corofn);

    fcontext_stack_t create_fcontext_stack(size_t size);
    void destroy_fcontext_stack(fcontext_stack_t* s);

#ifdef __cplusplus
}
#endif
