/* See LICENSE for license details. */

/*

Module: meat_main.c

Description:

    OS-independant main entry point of meat application.

*/

#include "meat_os.h"

#include "meat_main.h"

#include "meat_list.h"

#include "meat_time.h"

#include "meat_heap.h"

#include "meat_trace.h"

#include "meat_opts.h"

#include "meat_game.h"

#include "meat_file.h"

#include "meat_dbg.h"

#include "meat_ctxt.h"

static
void
print_string(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_file * const
        p_file,
    char const * const
        a_msg)
{
    char const *
        p_msg;

    p_msg =
        a_msg;

    while (
        *(
            p_msg))
    {
        meat_file_write_char(
            p_ctxt,
            p_file,
            *(
                p_msg));

        p_msg ++;
    }
}

/*

Structure: meat_main_impl

Description:

*/
struct meat_main_impl
{
    struct meat_ctxt
        o_ctxt;

    struct meat_dbg
        o_dbg;

    struct meat_trace
        o_trace;

    struct meat_heap
        o_heap;

    struct meat_opts
        o_opts;

    struct meat_file
        o_file_out;

    struct meat_file
        o_file_in;

    struct meat_game_list
        o_game_list;

    char
        b_input;

}; /* struct meat_main_impl */

static
void
    meat_main_impl_game_list_report_callback(
        struct meat_ctxt * const
            p_ctxt,
        void * const
            p_context,
        struct meat_game * const
            p_game)
{
    struct meat_main_impl * const
        p_main =
        p_context;

    struct meat_opts * const
        p_opts =
        &(
            p_main->o_opts);

    struct meat_file * const
        p_file_out =
        &(
            p_main->o_file_out);

    if (
        (
            p_game->i_game_time
            >= p_opts->i_begin)
        && (
            p_game->i_game_time
            <= p_opts->i_end))
    {
        char
            ac_game_time[64u];

        unsigned int
            i_date_len;

        i_date_len =
            meat_time_format_stamp(
                p_game->i_game_time,
                ac_game_time,
                sizeof(ac_game_time));

        print_string(
            p_ctxt,
            p_file_out,
            ac_game_time);

        {
            while (
                i_date_len
                < 28)
            {
                meat_file_write_char(
                    p_ctxt,
                    p_file_out,
                    ' ');

                i_date_len ++;
            }
        }

        print_string(
            p_ctxt,
            p_file_out,
            p_game->a_remarks);

        meat_file_write_char(
            p_ctxt,
            p_file_out,
            '\n');
    }

} /* meat_main_impl_game_list_report_callback() */

/* Print the selected range */
static
void
meat_main_impl_show_range(
    struct meat_main_impl * const
        p_main)
{
    struct meat_ctxt *
        p_ctxt;

    char
        ac_range_begin[64u];

    char
        ac_range_end[64u];

    p_ctxt =
        &(
            p_main->o_ctxt);

    meat_time_format_stamp(
        p_main->o_opts.i_begin,
        ac_range_begin,
        sizeof(ac_range_begin));

    meat_time_format_stamp(
        p_main->o_opts.i_end,
        ac_range_end,
        sizeof(ac_range_end));

    print_string(
        p_ctxt,
        &(
            p_main->o_file_out),
        "Range from ");

    print_string(
        p_ctxt,
        &(
            p_main->o_file_out),
        ac_range_begin);

    print_string(
        p_ctxt,
        &(
            p_main->o_file_out),
        " to ");

    print_string(
        p_ctxt,
        &(
            p_main->o_file_out),
        ac_range_end);

    print_string(
        p_ctxt,
        &(
            p_main->o_file_out),
        "\n");

} /* meat_main_impl_show_range() */

static
void
    meat_main_impl_game_list_report(
        struct meat_main_impl * const
            p_main)
{
    struct meat_ctxt *
        p_ctxt;

    p_ctxt =
        &(
            p_main->o_ctxt);

    meat_game_list_iterate(
        &(
            p_main->o_ctxt),
        &(
            p_main->o_game_list),
        &(
            meat_main_impl_game_list_report_callback),
        p_main);

} /* meat_main_impl_game_list_report() */

static
int
    meat_main_impl_dispatch(
        struct meat_main_impl * const
            p_main)
{
    int
        i_result;

    meat_main_impl_show_range(
        p_main);

    meat_main_impl_game_list_report(
        p_main);

    i_result =
        0;

    return
        i_result;

} /* meat_main_dispatch() */

static
char
    meat_main_impl_init(
        struct meat_main_impl * const
            p_main,
        unsigned int const
            argc,
        char const * const * const
            argv)
{
    char
        b_result;

    struct meat_ctxt *
        p_ctxt;

    p_ctxt =
        &(
            p_main->o_ctxt);

    p_ctxt->p_dbg =
        &(
            p_main->o_dbg);

    p_ctxt->p_trace =
        &(
            p_main->o_trace);

    p_ctxt->p_heap =
        &(
            p_main->o_heap);

    meat_dbg_init(
        p_ctxt,
        &(
            p_main->o_dbg));

    meat_trace_init(
        p_ctxt,
        &(
            p_main->o_trace));

    meat_heap_init(
        p_ctxt,
        &(
            p_main->o_heap));

    meat_file_init(
        p_ctxt,
        &(
            p_main->o_file_out),
        meat_file_type_stdout,
        NULL);

    meat_opts_init(
        &(
            p_main->o_opts),
        argc,
        argv);

    if (
        p_main->o_opts.i_end
        > p_main->o_opts.i_begin)
    {
        p_main->o_opts.i_end -= 10;

        p_main->b_input =
            meat_file_init(
                p_ctxt,
                &(
                    p_main->o_file_in),
                meat_file_type_stdin,
                NULL);

        if (
            p_main->b_input)
        {
            if (
                meat_game_list_init(
                    p_ctxt,
                    &(
                        p_main->o_game_list),
                    &(
                        p_main->o_file_in)))
            {
                meat_file_cleanup(
                    p_ctxt,
                    &(
                        p_main->o_file_in));

                p_main->b_input =
                    0;

                b_result =
                    1;

#if 0 /* not used */
                if (
                    !b_result)
                {
                    meat_game_list_cleanup(
                        p_ctxt,
                        &(
                            p_main->o_game_list));
                }
#endif /* not used */
            }
            else
            {
                b_result =
                    0;
            }

            if (
                !b_result)
            {
                if (
                    p_main->b_input)
                {
                    meat_file_cleanup(
                        p_ctxt,
                        &(
                            p_main->o_file_in));

                    p_main->b_input =
                        0;
                }
            }
        }
        else
        {
            b_result =
                0;
        }
    }
    else
    {
        print_string(
            p_ctxt,
            &(
                p_main->o_file_out),
            "wha?\n");

        b_result =
            0;
    }

    if (
        !b_result)
    {
        meat_opts_cleanup(
            &(
                p_main->o_opts));

        meat_file_cleanup(
            p_ctxt,
            &(
                p_main->o_file_out));

        meat_heap_cleanup(
            p_ctxt,
            &(
                p_main->o_heap));

        meat_trace_cleanup(
            p_ctxt,
            &(
                p_main->o_trace));

        meat_dbg_cleanup(
            p_ctxt,
            &(
                p_main->o_dbg));
    }

    return
        b_result;

} /* meat_main_impl_init() */

static
void
    meat_main_impl_cleanup(
        struct meat_main_impl * const
            p_main)
{
    struct meat_ctxt *
        p_ctxt;

    p_ctxt =
        &(
            p_main->o_ctxt);

    meat_game_list_cleanup(
        p_ctxt,
        &(
            p_main->o_game_list));

    if (
        p_main->b_input)
    {
        meat_file_cleanup(
            p_ctxt,
            &(
                p_main->o_file_in));

        p_main->b_input =
            0;
    }

    meat_file_cleanup(
        p_ctxt,
        &(
            p_main->o_file_out));

    meat_opts_cleanup(
        &(
            p_main->o_opts));

    meat_heap_cleanup(
        p_ctxt,
        &(
            p_main->o_heap));

    meat_trace_cleanup(
        p_ctxt,
        &(
            p_main->o_trace));

    meat_dbg_cleanup(
        p_ctxt,
        &(
            p_main->o_dbg));

} /* meat_main_impl_cleanup() */

/*

Function: meat_main

Description:

    OS independant entry point of meat application.  Create the main
    application object, dispatch the commands and then cleanup.

*/
int
    meat_main(
        unsigned int const
            argc,
        char const * const * const
            argv)
{
    int
        i_result;

    struct meat_main_impl
        o_main;

    struct meat_main_impl *
        p_main;

    p_main =
        &(
            o_main);

    /* Create the main application object */
    if (
        meat_main_impl_init(
            p_main,
            argc,
            argv))
    {
        /* Dispatch the commands */
        i_result =
            meat_main_impl_dispatch(
                p_main);

        /* Cleanup */
        meat_main_impl_cleanup(
            p_main);
    }
    else
    {
        /* Initialization failed */
        i_result =
            1;
    }

    return
        i_result;

} /* meat_main() */

/* end-of-file: meat_main.c */
