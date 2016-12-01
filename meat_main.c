/* See LICENSE for license details. */

/*

Module: meat_main.c

Description:

    OS-independant main entry point of meat application.

*/

#include "meat_os.h"

#include "meat_cfg.h"

#include "meat_main.h"

#include "meat_list.h"

#include "meat_time.h"

#include "meat_heap.h"

#if defined(MEAT_CFG_LEAK)
#include "meat_trace.h"
#endif /* #if defined(MEAT_CFG_LEAK) */

#include "meat_opts.h"

#include "meat_game.h"

#include "meat_file.h"

#if defined(MEAT_CFG_DBG)
#include "meat_dbg.h"
#endif /* #if defined(MEAT_CFG_DBG) */

#include "meat_ctxt.h"

static
void
print_string(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_file * const
        p_file,
    char const * const
        a_msg,
    size_t const
        i_msg_len)
{
    size_t
        i_offset;

    i_offset =
        0;

    while (
        i_offset
        < i_msg_len)
    {
        meat_file_write_char(
            p_ctxt,
            p_file,
            a_msg[i_offset]);

        i_offset ++;
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

#if defined(MEAT_CFG_DBG)
    struct meat_dbg
        o_dbg;
#endif /* #if defined(MEAT_CFG_DBG) */

#if defined(MEAT_CFG_LEAK)
    struct meat_trace
        o_trace;
#endif /* #if defined(MEAT_CFG_LEAK) */

    struct meat_heap
        o_heap;

    struct meat_opts
        o_opts;

    struct meat_file *
        p_file_out;

    struct meat_file *
        p_file_in;

    struct meat_game_list
        o_game_list;

#if defined(MEAT_CFG_DBG)
    char
        b_dbg;
#endif /* #if defined(MEAT_CFG_DBG) */

#if defined(MEAT_CFG_LEAK)
    char
        b_trace;
#endif /* #if defined(MEAT_CFG_LEAK) */

    char
        b_heap;

    char
        b_opts;

    char
        b_games;

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
        p_main->p_file_out;

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
            ac_game_time,
            i_date_len);

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
            p_game->a_remarks,
            p_game->i_remarks_len);

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

    int
        i_range_begin_len;

    int
        i_range_end_len;

    p_ctxt =
        &(
            p_main->o_ctxt);

    i_range_begin_len =
        meat_time_format_stamp(
            p_main->o_opts.i_begin,
            ac_range_begin,
            sizeof(ac_range_begin));

    i_range_end_len =
        meat_time_format_stamp(
            p_main->o_opts.i_end,
            ac_range_end,
            sizeof(ac_range_end));

    {
        static char const a_msg[] =
        {
            'R',
            'a',
            'n',
            'g',
            'e',
            ' ',
            'f',
            'r',
            'o',
            'm',
            ' '
        };

        print_string(
            p_ctxt,
            p_main->p_file_out,
            a_msg,
            sizeof(a_msg));
    }

    print_string(
        p_ctxt,
        p_main->p_file_out,
        ac_range_begin,
        i_range_begin_len);

    {
        static char const a_msg[] =
        {
            ' ',
            't',
            'o',
            ' '
        };

        print_string(
            p_ctxt,
            p_main->p_file_out,
            a_msg,
            sizeof(a_msg));
    }

    print_string(
        p_ctxt,
        p_main->p_file_out,
        ac_range_end,
        i_range_end_len);

    {
        static char const a_msg[] =
        {
            '\n'
        };

        print_string(
            p_ctxt,
            p_main->p_file_out,
            a_msg,
            sizeof(a_msg));
    }

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

#if defined(MEAT_CFG_DBG)
    p_main->b_dbg =
        0;
#endif /* #if defined(MEAT_CFG_DBG) */

#if defined(MEAT_CFG_LEAK)
    p_main->b_trace =
        0;
#endif /* #if defined(MEAT_CFG_LEAK) */

    p_main->b_heap =
        0;

    p_main->b_opts =
        0;

    p_main->p_file_in =
        0;

    p_main->p_file_out =
        0;

    p_main->b_games =
        0;

    p_ctxt =
        &(
            p_main->o_ctxt);

#if defined(MEAT_CFG_DBG)
    p_ctxt->p_dbg =
        &(
            p_main->o_dbg);
#endif /* #if defined(MEAT_CFG_DBG) */

#if defined(MEAT_CFG_LEAK)
    p_ctxt->p_trace =
        &(
            p_main->o_trace);
#endif /* #if defined(MEAT_CFG_LEAK) */

    p_ctxt->p_heap =
        &(
            p_main->o_heap);

#if defined(MEAT_CFG_DBG)
    meat_dbg_init(
        p_ctxt,
        &(
            p_main->o_dbg));

    p_main->b_dbg =
        1;
#endif /* #if defined(MEAT_CFG_DBG) */

#if defined(MEAT_CFG_LEAK)
    meat_trace_init(
        p_ctxt,
        &(
            p_main->o_trace));

    p_main->b_trace =
        1;
#endif /* #if defined(MEAT_CFG_LEAK) */

    meat_heap_init(
        p_ctxt,
        &(
            p_main->o_heap));

    p_main->b_heap =
        1;

    p_main->p_file_out =
        meat_file_create(
            p_ctxt,
            meat_file_type_stdout,
            NULL);

    meat_opts_init(
        &(
            p_main->o_opts),
        argc,
        (unsigned char const * const *)(argv));

    p_main->b_opts =
        1;

    if (
        p_main->o_opts.i_end
        > p_main->o_opts.i_begin)
    {
        p_main->o_opts.i_end -= 10;

        p_main->p_file_in =
            meat_file_create(
                p_ctxt,
                meat_file_type_stdin,
                NULL);

        if (
            p_main->p_file_in)
        {
            if (
                meat_game_list_init(
                    p_ctxt,
                    &(
                        p_main->o_game_list),
                    p_main->p_file_in))
            {
                p_main->b_games =
                    1;

                meat_file_destroy(
                    p_ctxt,
                    p_main->p_file_in);

                p_main->p_file_in =
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

                    p_main->b_games =
                        0;
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
                    p_main->p_file_in)
                {
                    meat_file_destroy(
                        p_ctxt,
                        p_main->p_file_in);

                    p_main->p_file_in =
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
        static char const a_msg[] =
        {
            'w',
            'h',
            'a',
            '?',
            '\n'
        };

        print_string(
            p_ctxt,
            p_main->p_file_out,
            a_msg,
            sizeof(a_msg));

        b_result =
            0;
    }

    if (
        !b_result)
    {
        if (
            p_main->b_opts)
        {
            meat_opts_cleanup(
                &(
                    p_main->o_opts));

            p_main->b_opts =
                0;
        }

        if (
            p_main->p_file_out)
        {
            meat_file_destroy(
                p_ctxt,
                p_main->p_file_out);

            p_main->p_file_out =
                (struct meat_file *)(
                    0);
        }

        if (
            p_main->b_heap)
        {
            meat_heap_cleanup(
                p_ctxt,
                &(
                    p_main->o_heap));

            p_main->b_heap =
                0;
        }

#if defined(MEAT_CFG_LEAK)
        if (
            p_main->b_trace)
        {
            meat_trace_cleanup(
                p_ctxt,
                &(
                    p_main->o_trace));

            p_main->b_trace =
                0;
        }
#endif /* #if defined(MEAT_CFG_LEAK) */

#if defined(MEAT_CFG_DBG)
        if (
            p_main->b_dbg)
        {
            meat_dbg_cleanup(
                p_ctxt,
                &(
                    p_main->o_dbg));

            p_main->b_dbg =
                0;
        }
#endif /* #if defined(MEAT_CFG_DBG) */
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

    if (
        p_main->b_games)
    {
        meat_game_list_cleanup(
            p_ctxt,
            &(
                p_main->o_game_list));

        p_main->b_games =
            0;
    }

    if (
        p_main->p_file_in)
    {
        meat_file_destroy(
            p_ctxt,
            p_main->p_file_in);

        p_main->p_file_in =
            0;
    }

    if (
        p_main->p_file_out)
    {
        meat_file_destroy(
            p_ctxt,
            p_main->p_file_out);

        p_main->p_file_out =
            (struct meat_file *)(
                0);
    }

    if (
        p_main->b_opts)
    {
        meat_opts_cleanup(
            &(
                p_main->o_opts));

        p_main->b_opts =
            0;
    }

    if (
        p_main->b_heap)
    {
        meat_heap_cleanup(
            p_ctxt,
            &(
                p_main->o_heap));

        p_main->b_heap =
            0;
    }

#if defined(MEAT_CFG_LEAK)
    if (
        p_main->b_trace)
    {
        meat_trace_cleanup(
            p_ctxt,
            &(
                p_main->o_trace));

        p_main->b_trace =
            0;
    }
#endif /* #if defined(MEAT_CFG_LEAK) */

#if defined(MEAT_CFG_DBG)
    if (
        p_main->b_dbg)
    {
        meat_dbg_cleanup(
            p_ctxt,
            &(
                p_main->o_dbg));

        p_main->b_dbg =
            0;
    }
#endif /* #if defined(MEAT_CFG_DBG) */

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
