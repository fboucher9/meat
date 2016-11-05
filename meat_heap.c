#include "meat_os.h"

#include "meat_heap.h"

void *
meat_heap_alloc(
    size_t const
        i_buf_len)
{
    return
        malloc(
            i_buf_len);

} /* meat_heap_alloc() */

void
meat_heap_free(
    void * const
        p_buf)
{
    free(
        p_buf);

} /* meat_heap_free() */

/* end-of-file: meat_heap.c */
