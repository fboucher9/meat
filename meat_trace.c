/* See LICENSE for license details. */

/*

Module: meat_trace.c

Description:

    Stack backtrace functions.

*/

#include "meat_os.h"

#include "meat_trace.h"

#if !defined(__CYGWIN__)
/* For backtrace() */
#include <execinfo.h>
#endif /* #if !defined(__CYGWIN__) */

static char b_meat_trace_init_done = 0;

static char const * p_meat_trace_argv0 = NULL;

/*

Function: meat_trace_init

Description:

*/
void
meat_trace_init(
    char const * const
        p_argv0)
{
    b_meat_trace_init_done =
        1;

    p_meat_trace_argv0 =
        p_argv0;

} /* meat_trace_init() */

/*

Function: meat_trace_cleanup

Description:

*/
void
meat_trace_cleanup(void)
{
    b_meat_trace_init_done =
        0;

    p_meat_trace_argv0 =
        NULL;

} /* meat_trace_cleanup() */

/*

Function: meat_trace_capture

Description:

*/
void
meat_trace_capture(
    void * * const
        a_stack,
    unsigned int const
        i_count)
{
    if (
        b_meat_trace_init_done)
    {
#if !defined(__CYGWIN__)
        backtrace(
            a_stack,
            i_count);
#else /* #if !defined(__CYGWIN__) */
        (void)(
            a_stack);
        (void)(
            i_count);
#endif /* #if !defined(__CYGWIN__) */

    }

} /* meat_trace_capture() */

/*

Function: meat_trace_report

Description:

*/
void
meat_trace_report(
    void * * const
        a_stack,
    unsigned int const
        i_count)
{
    if (
        b_meat_trace_init_done)
    {
#if !defined(__CYGWIN__)
        backtrace_symbols_fd(
            a_stack,
            i_count,
            1);
#else /* #if !defined(__CYGWIN__) */
        (void)(
            a_stack);
        (void)(
            i_count);
#endif /* #if !defined(__CYGWIN__) */

    }

} /* meat_trace_report() */

/* end-of-file: meat_trace.c */