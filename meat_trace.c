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

/* For dladdr() */
#define __USE_GNU
#include <dlfcn.h>

/* For system() */
#include <stdlib.h>

#endif /* #if !defined(__CYGWIN__) */

static char b_meat_trace_init_done = 0;

/*

Function: meat_trace_init

Description:

*/
void
meat_trace_init(void)
{
    b_meat_trace_init_done =
        1;

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

#if 0 /* fallback method */
        backtrace_symbols_fd(
            a_stack,
            i_count,
            1);
#endif /* fallback method */

        unsigned int
            i_index;

        i_index =
            0u;

        while (
            i_index < i_count)
        {
            void *
                p_stack_item;

            Dl_info
                o_info;

            int
                i_result;

            p_stack_item =
                a_stack[i_index];

            i_result =
                dladdr(
                    p_stack_item,
                    &(
                        o_info));

            if (
                0
                != i_result)
            {
                fprintf(stdout,
                    "[%d] %p -- ",
                    i_index,
                    p_stack_item);

                fflush(stdout);

                {
                    char
                        a_line[256u];

                    sprintf(
                        a_line,
                        "addr2line -e %s -f -s %p",
                        o_info.dli_fname,
                        p_stack_item);

                    system(a_line);
                }
            }
            else
            {
            }

            i_index ++;
        }

#else /* #if !defined(__CYGWIN__) */
        (void)(
            a_stack);
        (void)(
            i_count);
#endif /* #if !defined(__CYGWIN__) */

    }

} /* meat_trace_report() */

/* end-of-file: meat_trace.c */
