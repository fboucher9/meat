/* See LICENSE for license details. */

/*

Module: meat_opts.c

Description:

    Command-line options.

*/

#include "meat_os.h"

#include "meat_opts.h"

#include "meat_time.h"

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
        char const * const * const
            p_argv)
{
    time_t
        i_now;

    struct tm
        o_time_now;

    time_t
        i_range_begin;

    time_t
        i_range_end;

    int
        i_count;

    int
        i_month;

    int
        i_wday;

    i_now =
        time(
            NULL);

    get_day(
        i_now,
        &(
            o_time_now));

    if (
        i_argc > 1)
    {
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
        if (0 == strcmp(p_argv[1], "today"))
        {
            single_day_range(
                i_now,
                &i_range_begin,
                &i_range_end);
        }
        else if (0 == strcmp(p_argv[1], "tomorrow"))
        {
            single_day_range(
                i_now + offset_days(1),
                &i_range_begin,
                &i_range_end);
        }
        else if (0 == strcmp(p_argv[1], "yesterday"))
        {
            single_day_range(
                i_now - offset_days(1),
                &i_range_begin,
                &i_range_end);
        }
        else if (0 == strcmp(p_argv[1], "this"))
        {
            if (i_argc > 2)
            {
                if (0 == strcmp(p_argv[2], "day"))
                {
                    single_day_range(
                        i_now,
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(p_argv[2], "week"))
                {
                    single_week_range(
                        i_now,
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(p_argv[2], "month"))
                {
                    single_month_range(
                        i_now,
                        &i_range_begin,
                        &i_range_end);
                }
            }
        }
        else if (0 == strcmp(p_argv[1], "next"))
        {
            if (i_argc > 2)
            {
                if (0 == strcmp(p_argv[2], "day"))
                {
                    single_day_range(
                        i_now + offset_days(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(p_argv[2], "week"))
                {
                    single_week_range(
                        i_now + offset_weeks(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(p_argv[2], "month"))
                {
                    single_month_range(
                        find_middle_of_month(i_now, 1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (('0' <= p_argv[2][0]) && ('9' >= p_argv[2][0]))
                {
                    i_count = 1;
                    sscanf(p_argv[2], "%d", &i_count);
                    if (i_argc > 3)
                    {
                        if ((i_count > 1) && (0 == strcmp(p_argv[3], "days")))
                        {
                            align_range_to_day(
                                i_now + offset_days(1),
                                i_now + offset_days(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if ((i_count > 1) && (0 == strcmp(p_argv[3], "weeks")))
                        {
                            align_range_to_week(
                                i_now + offset_weeks(1),
                                i_now + offset_weeks(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if ((i_count > 1) && (0 == strcmp(p_argv[3], "months")))
                        {
                            align_range_to_month(
                                find_middle_of_month(i_now, 1),
                                find_middle_of_month(i_now, i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                    }
                }
                else if (-1 != (i_wday = which_wday(p_argv[2])))
                {
                    if (i_wday > o_time_now.tm_wday)
                    {
                        single_day_range(
                            i_now
                            + offset_days(
                                i_wday - o_time_now.tm_wday),
                            &i_range_begin,
                            &i_range_end);
                    }
                    else
                    {
                        single_day_range(
                            i_now
                            + offset_days(
                                7 + i_wday - o_time_now.tm_wday),
                            &i_range_begin,
                            &i_range_end);
                    }
                }
            }
        }
        else if (0 == strcmp(p_argv[1], "last"))
        {
            if (i_argc > 2)
            {
                if (0 == strcmp(p_argv[2], "day"))
                {
                    single_day_range(
                        i_now - offset_days(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(p_argv[2], "week"))
                {
                    single_week_range(
                        i_now - offset_weeks(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(p_argv[2], "month"))
                {
                    single_month_range(
                        find_middle_of_month(i_now, -1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (('0' <= p_argv[2][0]) && ('9' >= p_argv[2][0]))
                {
                    i_count = 1;
                    sscanf(p_argv[2], "%d", &i_count);
                    if (i_argc > 3)
                    {
                        if (i_count > 1)
                        {
                            if (0 == strcmp(p_argv[3], "days"))
                            {
                                align_range_to_day(
                                    i_now - offset_days(i_count),
                                    i_now - offset_days(1),
                                    &i_range_begin,
                                    &i_range_end);
                            }
                            else if (0 == strcmp(p_argv[3], "weeks"))
                            {
                                align_range_to_week(
                                    i_now - offset_weeks(i_count),
                                    i_now - offset_weeks(1),
                                    &i_range_begin,
                                    &i_range_end);
                            }
                            else if (0 == strcmp(p_argv[3], "months"))
                            {
                                align_range_to_month(
                                    find_middle_of_month(i_now, -i_count),
                                    find_middle_of_month(i_now, -1),
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
            i_count = 1;
            sscanf(p_argv[1], "%d", &i_count);
            if (i_argc > 3)
            {
                if (0 == strcmp(p_argv[3], "ago"))
                {
                    if (
                        (
                            (i_count > 1)
                            && (0 == strcmp(p_argv[2], "days")))
                        || (
                            (i_count == 1)
                            && (0 == strcmp(p_argv[2], "day"))))
                    {
                        single_day_range(
                            i_now - offset_days(i_count),
                            &i_range_begin,
                            &i_range_end);
                    }
                    else if (
                        (
                            (i_count > 1)
                            && (0 == strcmp(p_argv[2], "weeks")))
                        || (
                            (i_count == 1)
                            && (0 == strcmp(p_argv[2], "week"))))
                    {
                        single_week_range(
                            i_now - offset_weeks(i_count),
                            &i_range_begin,
                            &i_range_end);
                    }
                    else if (
                        (
                            (i_count > 1)
                            && (0 == strcmp(p_argv[2], "months")))
                        || (
                            (i_count == 1)
                            && (0 == strcmp(p_argv[2], "month"))))
                    {
                        single_month_range(
                            find_middle_of_month(i_now, -i_count),
                            &i_range_begin,
                            &i_range_end);
                    }
                }
            }
        }
        else if (0 == strcmp(p_argv[1], "in"))
        {
            if (i_argc > 2)
            {
                if (('0' <= p_argv[2][0]) && ('9' >= p_argv[2][0]))
                {
                    i_count = 1;
                    sscanf(p_argv[2], "%d", &i_count);
                    if (i_argc > 3)
                    {
                        if (
                            (
                                (i_count > 1)
                                && (0 == strcmp(p_argv[3], "days")))
                            || (
                                (i_count == 1)
                                && (0 == strcmp(p_argv[3], "day"))))
                        {
                            single_day_range(
                                i_now + offset_days(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if (
                            (
                                (i_count > 1)
                                && (0 == strcmp(p_argv[3], "weeks")))
                            || (
                                (i_count == 1)
                                && (0 == strcmp(p_argv[3], "week"))))
                        {
                            single_week_range(
                                i_now + offset_weeks(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if (
                            (
                                (i_count > 1)
                                && (0 == strcmp(p_argv[3], "months")))
                            || (
                                (i_count == 1)
                                && (0 == strcmp(p_argv[3], "month"))))
                        {
                            single_month_range(
                                find_middle_of_month(i_now, i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                    }
                }
            }
        }
        else if (-1 != (i_month = which_month(p_argv[1])))
        {
            time_t
                i_random_day_of_month;

            if (o_time_now.tm_mon > i_month)
            {
                i_random_day_of_month =
                    init_day(
                        0,
                        12,
                        11,
                        i_month,
                        o_time_now.tm_year + 1);
            }
            else
            {
                i_random_day_of_month =
                    init_day(
                        0,
                        12,
                        11,
                        i_month,
                        o_time_now.tm_year);
            }

            single_month_range(
                i_random_day_of_month,
                &i_range_begin,
                &i_range_end);
        }
        else if (-1 != (i_wday = which_wday(p_argv[1])))
        {
            single_day_range(
                i_now
                + offset_days(
                    i_wday - o_time_now.tm_wday),
                &i_range_begin,
                &i_range_end);
        }
    }
    else
    {
        align_range_to_week(
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
