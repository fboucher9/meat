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

struct meat_list
o_game_list =
{
    &(
        o_game_list),
    &(
        o_game_list)
};

struct meat_game
{
    struct meat_list
        o_list;

    time_t
        i_game_time;

    char
        a_remarks[256u];

};

char *
strip_trailing_spaces(
    char * const
        p_buf)
{
    int
        i_buf_len;

    i_buf_len =
        strlen(
            p_buf);

    while (
        (
            i_buf_len > 0)
        && (
            (
                ' ' == p_buf[i_buf_len - 1])
            || (
                '\n' == p_buf[i_buf_len - 1])))
    {
        p_buf[i_buf_len - 1] = '\000';

        i_buf_len --;
    }

    return p_buf;
}

char const *
skip_leading_spaces(
    char const * const
        p_buf)
{
    char const *
        p_iterator;

    p_iterator =
        p_buf;

    while (
        ' ' == *p_iterator)
    {
        p_iterator ++;
    }

    return p_iterator;
}

/* Load games from input file */
void
load_games(
    FILE * p_input)
{
    char *
        p_result;

    char
        b_continue;

    char
        a_line[256u];

    b_continue =
        1;

    while (
        b_continue)
    {
        p_result =
            fgets(
                a_line,
                sizeof(
                    a_line),
                p_input);

        if (
            p_result)
        {
            struct meat_game *
                p_game =
                (struct meat_game *)(
                    meat_heap_alloc(
                        sizeof(
                            struct meat_game)));

            if (
                p_game)
            {
                a_line[255u] =
                    '\000';

                p_game->i_game_time = 0;

                p_game->a_remarks[0u] = '\000';

                {
                    unsigned int
                        year;

                    unsigned int
                        month;

                    unsigned int
                        day;

                    unsigned int
                        hour;

                    unsigned int
                        minute;

                    int
                        i_offset;

                    sscanf(
                        a_line,
                        "%u%u%u%u%u%n",
                        &(
                            year),
                        &(
                            month),
                        &(
                            day),
                        &(
                            hour),
                        &(
                            minute),
                        &(
                            i_offset));

                    p_game->i_game_time =
                        init_day(
                            0,
                            minute,
                            hour,
                            day,
                            month - 1,
                            year - 1900);

                    strcpy(
                        p_game->a_remarks,
                        skip_leading_spaces(
                            a_line + i_offset));

                    strip_trailing_spaces(
                        p_game->a_remarks);
                }

                meat_list_init(
                    &(
                        p_game->o_list));

                meat_list_join(
                    &(
                        p_game->o_list),
                    &(
                        o_game_list));
            }
            else
            {
                b_continue =
                    0;
            }
        }
        else
        {
            b_continue =
                0;
        }
    }

#if 0 /* debug */
    {
        struct meat_list * iterator;

        iterator = o_game_list.p_next;

        while (iterator != &o_game_list)
        {
            struct meat_game const * p_game = (struct meat_game const *)(iterator);

            printf("%lu {%s}\n",
                (unsigned long int)(
                    p_game->i_game_time),
                p_game->a_remarks);

            iterator = iterator->p_next;
        }
    }
#endif /* debug */
}


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
        o_opts.i_end -= 10;

        if (
            1)
        {
            FILE *
                p_input;

            p_input =
                fopen(
                    "games.txt",
                    "r");

            if (
                p_input)
            {
                load_games(
                    p_input);

                fclose(
                    p_input);
            }
        }

        if (
            1)
        {
            /* Print the selected range */
            char ac_range_begin[64u];

            char ac_range_end[64u];

            format_date(
                o_opts.i_begin,
                ac_range_begin);

            format_date(
                o_opts.i_end,
                ac_range_end);

            printf("Range from %s to %s\n", ac_range_begin, ac_range_end);
        }

        if (
            1)
        {
            struct meat_list const * iterator;

            iterator = o_game_list.p_next;

            while (iterator != &o_game_list)
            {
                struct meat_game const *
                    p_game;

                p_game =
                    (struct meat_game const *)(
                        iterator);

                if (
                    (
                        p_game->i_game_time
                        >= o_opts.i_begin)
                    && (
                        p_game->i_game_time
                        <= o_opts.i_end))
                {
                    char ac_game_time[64u];

                    format_date(
                        p_game->i_game_time,
                        ac_game_time);

                    printf("%-26s  %s\n",
                        ac_game_time,
                        p_game->a_remarks);
                }

                iterator = iterator->p_next;
            }
        }

        if (
            1)
        {
            /* Free all of the games */
            struct meat_list *
                p_iterator;

            struct meat_list *
                p_next;

            struct meat_game *
                p_game;

            p_iterator =
                o_game_list.p_next;

            while (
                p_iterator
                != &o_game_list)
            {
                p_next =
                    p_iterator->p_next;

                p_game =
                    (struct meat_game *)(
                        p_iterator);

                meat_list_join(
                    &(
                        p_game->o_list),
                    &(
                        p_game->o_list));

                meat_heap_free(
                    (void *)(
                        p_game));

                p_iterator =
                    p_next;
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
