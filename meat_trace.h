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

#if defined(INC_MEAT_TRACE_H)
#error include meat_trace.h once
#endif /* #if defined(INC_MEAT_TRACE_H) */

#define INC_MEAT_TRACE_H

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_trace_init(
    char const * const
        p_argv0);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_trace_cleanup(void);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_trace_capture(
    void * * const
        a_stack,
    unsigned int const
        i_count);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_trace_report(
    void * * const
        a_stack,
    unsigned int const
        i_count);

/* end-of-file: meat_trace.h */
