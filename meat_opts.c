/* See LICENSE for license details. */

/*

Module: meat_opts.c

Description:

    Command-line options.

*/

#include "meat_os.h"

#include "meat_opts.h"

#include "meat_time.h"

#include "meat_string.h"

static unsigned char const g_word_today[] =
{
    't',
    'o',
    'd',
    'a',
    'y'
};

static unsigned char const g_word_tomorrow[] =
{
    't',
    'o',
    'm',
    'o',
    'r',
    'r',
    'o',
    'w'
};

static unsigned char const g_word_yesterday[] =
{
    'y',
    'e',
    's',
    't',
    'e',
    'r',
    'd',
    'a',
    'y'
};

static unsigned char const g_word_this[] =
{
    't',
    'h',
    'i',
    's'
};

static unsigned char const g_word_day[] =
{
    'd',
    'a',
    'y'
};

static unsigned char const g_word_week[] =
{
    'w',
    'e',
    'e',
    'k'
};

static unsigned char const g_word_month[] =
{
    'm',
    'o',
    'n',
    't',
    'h'
};

static unsigned char const g_word_days[] =
{
    'd',
    'a',
    'y',
    's'
};

static unsigned char const g_word_weeks[] =
{
    'w',
    'e',
    'e',
    'k',
    's'
};

static unsigned char const g_word_months[] =
{
    'm',
    'o',
    'n',
    't',
    'h',
    's'
};

static unsigned char const g_word_next[] =
{
    'n',
    'e',
    'x',
    't'
};

static unsigned char const g_word_last[] =
{
    'l',
    'a',
    's',
    't'
};

static unsigned char const g_word_ago[] =
{
    'a',
    'g',
    'o'
};

static unsigned char const g_word_in[] =
{
    'i',
    'n'
};

/*

Function: meat_opts_init

Description:

    Initialize the meat_opts structure by parsing the command-line options.

Parameters:

    p_opts
        Pointer to meat_opts structure.
    i_argc
        Number of command-line arguments
    p_argv
        Array of command-line arguments

Returns: None.

Comments: None.

*/
void
    meat_opts_init(
        struct meat_opts * const
            p_opts,
        unsigned int const
            i_argc,
        unsigned char const * const * const
            p_argv)
{
    signed long int
        i_now;

    struct meat_time_info
        o_time_now;

    signed long int
        i_range_begin;

    signed long int
        i_range_end;

    size_t
        p_argl[4u];

    int
        i_count;

    int
        i_month;

    int
        i_wday;

    i_now =
        meat_time_get_stamp_now();

    meat_time_get_info_from_stamp(
        i_now,
        &(
            o_time_now));

    if (
        i_argc > 1)
    {
        {
            unsigned int
                i_argi;

            for (i_argi = 1; (i_argi < i_argc) && (i_argi < 4u); i_argi++)
            {
                p_argl[i_argi] =
                    meat_string_find_null(
                        p_argv[i_argi],
                        ~0u);
            }
        }

        i_range_begin =
            i_now;

        i_range_end =
            i_now - 1;

        /* today */
        /* yesterday */
        /* tomorrow */
        /* jan|feb|mar|... */
        /* mon|tue|web|... */
        /* next [N] day(s),week(s),month(s) */
        /* last [N] day(s),week(s),month(s) */
        /* this day,week,month */
        /* [N] day(s) ago */
        /* [N] week(s) ago */
        /* [N] month(s) ago */
        /* in [N] day(s) */
        /* in [N] week(s) */
        /* in [N] month(s) */
        /* next|last|this Monday... */
        /* next|last|this October... */

        if (0 == meat_string_compare(p_argv[1u], p_argl[1u], g_word_today, sizeof(g_word_today)))
        {
            meat_time_single_day_range(
                i_now,
                &i_range_begin,
                &i_range_end);
        }
        else if (0 == meat_string_compare(p_argv[1u], p_argl[1u], g_word_tomorrow, sizeof(g_word_tomorrow)))
        {
            meat_time_single_day_range(
                i_now + meat_time_offset_days(1),
                &i_range_begin,
                &i_range_end);
        }
        else if (0 == meat_string_compare(p_argv[1u], p_argl[1u], g_word_yesterday, sizeof(g_word_yesterday)))
        {
            meat_time_single_day_range(
                i_now - meat_time_offset_days(1),
                &i_range_begin,
                &i_range_end);
        }
        else if (0 == meat_string_compare(p_argv[1u], p_argl[1u], g_word_this, sizeof(g_word_this)))
        {
            if (i_argc > 2)
            {
                if (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_day, sizeof(g_word_day)))
                {
                    meat_time_single_day_range(
                        i_now,
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_week, sizeof(g_word_week)))
                {
                    meat_time_single_week_range(
                        i_now,
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_month, sizeof(g_word_month)))
                {
                    meat_time_single_month_range(
                        i_now,
                        &i_range_begin,
                        &i_range_end);
                }
            }
        }
        else if (0 == meat_string_compare(p_argv[1u], p_argl[1u], g_word_next, sizeof(g_word_next)))
        {
            if (i_argc > 2)
            {
                if (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_day, sizeof(g_word_day)))
                {
                    meat_time_single_day_range(
                        i_now + meat_time_offset_days(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_week, sizeof(g_word_week)))
                {
                    meat_time_single_week_range(
                        i_now + meat_time_offset_weeks(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_month, sizeof(g_word_month)))
                {
                    meat_time_single_month_range(
                        meat_time_find_middle_of_month(i_now, 1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (('0' <= p_argv[2][0]) && ('9' >= p_argv[2][0]))
                {
                    i_count =
                        meat_string_scan_decimal(
                            p_argv[2u],
                            p_argl[2u]);

                    if (i_argc > 3)
                    {
                        if ((i_count > 1) && (0 == meat_string_compare(p_argv[3u], p_argl[3u], g_word_days, sizeof(g_word_days))))
                        {
                            meat_time_align_range_to_day(
                                i_now + meat_time_offset_days(1),
                                i_now + meat_time_offset_days(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if ((i_count > 1) && (0 == meat_string_compare(p_argv[3u], p_argl[3u], g_word_weeks, sizeof(g_word_weeks))))
                        {
                            meat_time_align_range_to_week(
                                i_now + meat_time_offset_weeks(1),
                                i_now + meat_time_offset_weeks(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if ((i_count > 1) && (0 == meat_string_compare(p_argv[3u], p_argl[3u], g_word_months, sizeof(g_word_months))))
                        {
                            meat_time_align_range_to_month(
                                meat_time_find_middle_of_month(i_now, 1),
                                meat_time_find_middle_of_month(i_now, i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                    }
                }
                else if (-1 != (i_wday = meat_time_which_day_of_week(p_argv[2u], p_argl[2u])))
                {
                    if (i_wday > o_time_now.i_day_of_week)
                    {
                        meat_time_single_day_range(
                            i_now
                            + meat_time_offset_days(
                                i_wday - o_time_now.i_day_of_week),
                            &i_range_begin,
                            &i_range_end);
                    }
                    else
                    {
                        meat_time_single_day_range(
                            i_now
                            + meat_time_offset_days(
                                7 + i_wday - o_time_now.i_day_of_week),
                            &i_range_begin,
                            &i_range_end);
                    }
                }
            }
        }
        else if (0 == meat_string_compare(p_argv[1u], p_argl[1u], g_word_last, sizeof(g_word_last)))
        {
            if (i_argc > 2)
            {
                if (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_day, sizeof(g_word_day)))
                {
                    meat_time_single_day_range(
                        i_now - meat_time_offset_days(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_week, sizeof(g_word_week)))
                {
                    meat_time_single_week_range(
                        i_now - meat_time_offset_weeks(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_month, sizeof(g_word_month)))
                {
                    meat_time_single_month_range(
                        meat_time_find_middle_of_month(i_now, -1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (('0' <= p_argv[2][0]) && ('9' >= p_argv[2][0]))
                {
                    i_count =
                        meat_string_scan_decimal(
                            p_argv[2u],
                            p_argl[2u]);
                    if (i_argc > 3)
                    {
                        if (i_count > 1)
                        {
                            if (0 == meat_string_compare(p_argv[3u], p_argl[3u], g_word_days, sizeof(g_word_days)))
                            {
                                meat_time_align_range_to_day(
                                    i_now - meat_time_offset_days(i_count),
                                    i_now - meat_time_offset_days(1),
                                    &i_range_begin,
                                    &i_range_end);
                            }
                            else if (0 == meat_string_compare(p_argv[3u], p_argl[3u], g_word_weeks, sizeof(g_word_weeks)))
                            {
                                meat_time_align_range_to_week(
                                    i_now - meat_time_offset_weeks(i_count),
                                    i_now - meat_time_offset_weeks(1),
                                    &i_range_begin,
                                    &i_range_end);
                            }
                            else if (0 == meat_string_compare(p_argv[3u], p_argl[3u], g_word_months, sizeof(g_word_months)))
                            {
                                meat_time_align_range_to_month(
                                    meat_time_find_middle_of_month(i_now, -i_count),
                                    meat_time_find_middle_of_month(i_now, -1),
                                    &i_range_begin,
                                    &i_range_end);
                            }
                        }
                    }
                }
            }
        }
        else if (('0' <= p_argv[1][0]) && ('9' >= p_argv[1][0]))
        {
            /* */
            i_count =
                meat_string_scan_decimal(
                    p_argv[1u],
                    p_argl[1u]);

            if (i_argc > 3)
            {
                if (0 == meat_string_compare(p_argv[3u], p_argl[3u], g_word_ago, sizeof(g_word_ago)))
                {
                    if (
                        (
                            (i_count > 1)
                            && (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_days, sizeof(g_word_days))))
                        || (
                            (i_count == 1)
                            && (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_day, sizeof(g_word_day)))))
                    {
                        meat_time_single_day_range(
                            i_now - meat_time_offset_days(i_count),
                            &i_range_begin,
                            &i_range_end);
                    }
                    else if (
                        (
                            (i_count > 1)
                            && (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_weeks, sizeof(g_word_weeks))))
                        || (
                            (i_count == 1)
                            && (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_week, sizeof(g_word_week)))))
                    {
                        meat_time_single_week_range(
                            i_now - meat_time_offset_weeks(i_count),
                            &i_range_begin,
                            &i_range_end);
                    }
                    else if (
                        (
                            (i_count > 1)
                            && (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_months, sizeof(g_word_months))))
                        || (
                            (i_count == 1)
                            && (0 == meat_string_compare(p_argv[2u], p_argl[2u], g_word_month, sizeof(g_word_month)))))
                    {
                        meat_time_single_month_range(
                            meat_time_find_middle_of_month(i_now, -i_count),
                            &i_range_begin,
                            &i_range_end);
                    }
                }
            }
        }
        else if (0 == meat_string_compare(p_argv[1u], p_argl[1u], g_word_in, sizeof(g_word_in)))
        {
            if (i_argc > 2)
            {
                if (('0' <= p_argv[2][0]) && ('9' >= p_argv[2][0]))
                {
                    i_count =
                        meat_string_scan_decimal(
                            p_argv[2u],
                            p_argl[2u]);
                    if (i_argc > 3)
                    {
                        if (
                            (
                                (i_count > 1)
                                && (0 == meat_string_compare(p_argv[3u], p_argl[3u], g_word_days, sizeof(g_word_days))))
                            || (
                                (i_count == 1)
                                && (0 == meat_string_compare(p_argv[3u], p_argl[3u], g_word_day, sizeof(g_word_day)))))
                        {
                            meat_time_single_day_range(
                                i_now + meat_time_offset_days(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if (
                            (
                                (i_count > 1)
                                && (0 == meat_string_compare(p_argv[3u], p_argl[3u], g_word_weeks, sizeof(g_word_weeks))))
                            || (
                                (i_count == 1)
                                && (0 == meat_string_compare(p_argv[3u], p_argl[3u], g_word_week, sizeof(g_word_week)))))
                        {
                            meat_time_single_week_range(
                                i_now + meat_time_offset_weeks(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if (
                            (
                                (i_count > 1)
                                && (0 == meat_string_compare(p_argv[3u], p_argl[3u], g_word_months, sizeof(g_word_months))))
                            || (
                                (i_count == 1)
                                && (0 == meat_string_compare(p_argv[3u], p_argl[3u], g_word_month, sizeof(g_word_month)))))
                        {
                            meat_time_single_month_range(
                                meat_time_find_middle_of_month(i_now, i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                    }
                }
            }
        }
        else if (-1 != (i_month = meat_time_which_month(p_argv[1u], p_argl[1u])))
        {
            signed long int
                i_random_day_of_month;

            struct meat_time_info
                o_random_day_of_month;

            o_random_day_of_month.i_minute =
                0;

            o_random_day_of_month.i_hour =
                12;

            o_random_day_of_month.i_day_of_month =
                11;

            o_random_day_of_month.i_month =
                i_month;

            if (o_time_now.i_month > i_month)
            {
                o_random_day_of_month.i_year =
                    o_time_now.i_year + 1;
            }
            else
            {
                o_random_day_of_month.i_year =
                    o_time_now.i_year;
            }

            i_random_day_of_month =
                meat_time_get_stamp_from_info(
                    &(
                        o_random_day_of_month));

            meat_time_single_month_range(
                i_random_day_of_month,
                &i_range_begin,
                &i_range_end);
        }
        else if (-1 != (i_wday = meat_time_which_day_of_week(p_argv[1u], p_argl[1u])))
        {
            meat_time_single_day_range(
                i_now
                + meat_time_offset_days(
                    i_wday - o_time_now.i_day_of_week),
                &i_range_begin,
                &i_range_end);
        }
    }
    else
    {
        meat_time_align_range_to_week(
            i_now,
            i_now,
            &i_range_begin,
            &i_range_end);
    }

    p_opts->i_begin =
        i_range_begin;

    p_opts->i_end =
        i_range_end;

} /* meat_opts_init() */

/*

Function: meat_opts_cleanup

Description:

    Free resource and undo initialization performed by meat_opts_init().

Parameters:

    p_opts

        Pointer to meat_opts structure.

Returns:

    None.

Comments:

    None.

*/
void
    meat_opts_cleanup(
        struct meat_opts * const
            p_opts)
{
    p_opts->i_begin =
        0;

    p_opts->i_end =
        0;

} /* meat_opts_cleanup() */

/* end-of-file: meat_opts.c */
