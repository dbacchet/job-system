#include "fcontext/fcontext.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

// create a stack object on the heap
fcontext_stack_t create_fcontext_stack(size_t size_) {
    assert(size_>0);
    fcontext_stack_t s;
    s.sptr = NULL;
    s.ssize = 0;

    void *vp = malloc(size_);
    if (!vp)
        return s;
    // the stack pointer points at the top of the stack
    s.sptr = (char*)vp + size_;
    s.ssize = size_;
    return s;
}

void destroy_fcontext_stack(fcontext_stack_t* s) {
    void *vp = (char*)s->sptr - s->ssize;
    free(vp);
    memset(s, 0x00, sizeof(fcontext_stack_t));
}

