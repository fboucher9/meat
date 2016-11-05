/* See LICENSE for license details. */

/*

Module: meat_heap.h

Description:

    Wrappers for heap management functions.  This module adds extra features
    such as memory leak detection and buffer overrun detection.

*/

/* Header file dependencies */
#if !defined(INC_MEAT_OS_H)
#error include meat_os.h first
#endif /* #if !defined(INC_MEAT_OS_H) */

/* Reverse include guard */
#if defined(INC_MEAT_HEAP_H)
#error include meat_heap.h once
#endif /* #if defined(INC_MEAT_HEAP_H) */

#define INC_MEAT_HEAP_H

/* Public meat_heap functions */

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void *
meat_heap_alloc(
    size_t const
        i_buf_len);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_heap_free(
    void * const
        p_buf);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_heap_init(void);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_heap_cleanup(void);

/* end-of-file: meat_heap.h */
