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

#include "meat_opts.h"

#include "meat_game.h"

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
    meat_game_report_callback(
        void * const
            p_context,
        struct meat_game * const
            p_game)
{
    struct meat_opts * const
        p_opts =
        (struct meat_opts *)(
            p_context);

    if (
        (
            p_game->i_game_time
            >= p_opts->i_begin)
        && (
            p_game->i_game_time
            <= p_opts->i_end))
    {
        char ac_game_time[64u];

        format_date(
            p_game->i_game_time,
            ac_game_time);

        printf("%-26s  %s\n",
            ac_game_time,
            p_game->a_remarks);
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

    meat_heap_init();

    meat_opts_init(
        &(
            o_opts),
        argc,
        argv);

    if (
        o_opts.i_end
        > o_opts.i_begin)
    {
        FILE *
            p_input;

        o_opts.i_end -= 10;

        p_input =
            fopen(
                "games.txt",
                "r");

        if (
            p_input)
        {
            struct meat_game_list
                o_game_list;

            if (
                meat_game_list_init(
                    &(
                        o_game_list),
                    p_input))
            {
                fclose(
                    p_input);

                p_input =
                    NULL;

                if (
                    1)
                {
                    /* Print the selected range */
                    char
                        ac_range_begin[64u];

                    char
                        ac_range_end[64u];

                    format_date(
                        o_opts.i_begin,
                        ac_range_begin);

                    format_date(
                        o_opts.i_end,
                        ac_range_end);

                    printf("Range from %s to %s\n", ac_range_begin, ac_range_end);
                }

                meat_game_list_iterate(
                    &(
                        o_game_list),
                    &(
                        meat_game_report_callback),
                    &(
                        o_opts));

                meat_game_list_cleanup(
                    &(
                        o_game_list));
            }

            if (
                p_input)
            {
                fclose(
                    p_input);

                p_input =
                    NULL;
            }
        }
    }
    else
    {
        printf("wha?\n");
    }

    meat_opts_cleanup(
        &(
            o_opts));

    meat_heap_cleanup();

    return 0;

} /* meat_main() */

/* end-of-file: meat_main.c */
