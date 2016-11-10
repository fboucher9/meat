/* See LICENSE for license details. */

/*

Module: meat_main.c

Description:

*/

#include "meat_os.h"

#include "meat_list.h"

#include "meat_time.h"

#include "meat_main.h"

#include "meat_heap.h"

#include "meat_trace.h"

#include "meat_opts.h"

#include "meat_game.h"

#include "meat_file.h"

/*

Interface:

    this week
    next week
    last week
    next n weeks
    last n weeks

    this month
    next month
    last month
    next n months
    last n months

    first week of month
    week of x [y [year]]
    month of x [year]

    this year
    next year
    last year

    next game
    last game
    next N games
    last N games

    from date to date

*/

static
void
print_string(
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
            p_file,
            *(
                p_msg));

        p_msg ++;
    }
}

struct meat_game_report_context
{
    struct meat_opts *
        p_opts;

    struct meat_file *
        p_file_out;

}; /* struct meat_game_report_context */

static
void
    meat_game_report_callback(
        void * const
            p_context,
        struct meat_game * const
            p_game)
{
    struct meat_game_report_context *
        p_report_context =
        (struct meat_game_report_context *)(
            p_context);

    struct meat_opts * const
        p_opts =
        p_report_context->p_opts;

    struct meat_file * const
        p_file_out =
        p_report_context->p_file_out;

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
            meat_time_format_date(
                p_game->i_game_time,
                ac_game_time,
                sizeof(ac_game_time));

        print_string(
            p_file_out,
            ac_game_time);

        {
            while (
                i_date_len
                < 28)
            {
                meat_file_write_char(
                    p_file_out,
                    ' ');

                i_date_len ++;
            }
        }

        print_string(
            p_file_out,
            p_game->a_remarks);

        meat_file_write_char(
            p_file_out,
            '\n');
    }

} /* meat_game_report_callback() */

int
    meat_main(
        unsigned int const
            argc,
        char const * const * const
            argv)
{
    struct meat_opts
        o_opts;

    struct meat_file
        o_file_out;

    meat_trace_init();

    meat_heap_init();

    meat_file_init(
        &(
            o_file_out),
        meat_file_type_stdout,
        NULL);

    meat_opts_init(
        &(
            o_opts),
        argc,
        argv);

    if (
        o_opts.i_end
        > o_opts.i_begin)
    {
        char
            b_input;

        struct meat_file
            o_file_in;

        o_opts.i_end -= 10;

        b_input =
            meat_file_init(
                &(
                    o_file_in),
                meat_file_type_stdin,
                NULL);

        if (
            b_input)
        {
            struct meat_game_list
                o_game_list;

            if (
                meat_game_list_init(
                    &(
                        o_game_list),
                    &(
                        o_file_in)))
            {
                meat_file_cleanup(
                    &(
                        o_file_in));

                b_input =
                    0;

                {
                    /* Print the selected range */
                    char
                        ac_range_begin[64u];

                    char
                        ac_range_end[64u];

                    meat_time_format_date(
                        o_opts.i_begin,
                        ac_range_begin,
                        sizeof(ac_range_begin));

                    meat_time_format_date(
                        o_opts.i_end,
                        ac_range_end,
                        sizeof(ac_range_end));

                    print_string(
                        &(
                            o_file_out),
                        "Range from ");

                    print_string(
                        &(
                            o_file_out),
                        ac_range_begin);

                    print_string(
                        &(
                            o_file_out),
                        " to ");

                    print_string(
                        &(
                            o_file_out),
                        ac_range_end);

                    print_string(
                        &(
                            o_file_out),
                        "\n");
                }

                {
                    struct meat_game_report_context
                        o_report_context;

                    o_report_context.p_opts =
                        &(
                            o_opts);

                    o_report_context.p_file_out =
                        &(
                            o_file_out);

                    meat_game_list_iterate(
                        &(
                            o_game_list),
                        &(
                            meat_game_report_callback),
                        &(
                            o_report_context));
                }

                meat_game_list_cleanup(
                    &(
                        o_game_list));
            }

            if (
                b_input)
            {
                meat_file_cleanup(
                    &(
                        o_file_in));

                b_input =
                    0;
            }
        }
    }
    else
    {
        print_string(
            &(
                o_file_out),
            "wha?\n");
    }

    meat_file_cleanup(
        &(
            o_file_out));

    meat_opts_cleanup(
        &(
            o_opts));

    meat_heap_cleanup();

    meat_trace_cleanup();

    return 0;

} /* meat_main() */

/* end-of-file: meat_main.c */
