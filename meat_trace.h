/* See LICENSE for license details. */

/*

Module: meat_trace.h

Description:

    Stack backtrace functions.

*/

/* Header file dependencies */
#if !defined(INC_MEAT_OS_H)
#error include meat_os.h first
#endif /* #if !defined(INC_MEAT_OS_H) */

#if !defined(INC_MEAT_CFG_H)
#error include meat_cfg.h before
#endif /* #if !defined(INC_MEAT_CFG_H) */

/* Validate configuration */
#if !defined(MEAT_CFG_LEAK)
#error feature is disabled
#endif /* #if !defined(MEAT_CFG_LEAK) */

/* Reverse include guard */
#if defined(INC_MEAT_TRACE_H)
#error include meat_trace.h once
#endif /* #if defined(INC_MEAT_TRACE_H) */

#define INC_MEAT_TRACE_H

struct meat_ctxt;

struct meat_trace
{
    char
        b_init;

}; /* struct meat_trace */

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_trace_init(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_trace * const
        p_trace);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_trace_cleanup(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_trace * const
        p_trace);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_trace_capture(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_trace * const
        p_trace,
    void * * const
        a_stack,
    unsigned int const
        i_count);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_trace_report(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_trace * const
        p_trace,
    void * * const
        a_stack,
    unsigned int const
        i_count);

/* end-of-file: meat_trace.h */
