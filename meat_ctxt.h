/* See LICENSE for license details. */

/*

Module: meat_ctxt.h

Description:

    Execution context.  Provide access to commonly used objects.

*/

/* Header file dependencies */
#if !defined(INC_MEAT_OS_H)
#error include meat_os.h first
#endif /* #if !defined(INC_MEAT_OS_H) */

/* Reverse include guard */
#if defined(INC_MEAT_CTXT_H)
#error include meat_ctxt.h once
#endif /* #if defined(INC_MEAT_CTXT_H) */

/* Predefine object handles */
struct meat_dbg;

struct meat_trace;

struct meat_heap;

/*

Structure: meat_ctxt

Description:

    Group of pointers to objects.

*/
struct meat_ctxt
{
    struct meat_dbg *
        p_dbg;

    struct meat_trace *
        p_trace;

    struct meat_heap *
        p_heap;

}; /* struct meat_ctxt */

/* end-of-file: meat_ctxt.h */
