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
    signed long int
        i_now;

    struct meat_time_info
        o_time_now;

    signed long int
        i_range_begin;

    signed long int
        i_range_end;

    int
        i_count;

    int
        i_month;

    int
        i_wday;

    i_now =
        (signed long int)(
            time(
                NULL) / 60l);

    meat_time_get_day(
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
            meat_time_single_day_range(
                i_now,
                &i_range_begin,
                &i_range_end);
        }
        else if (0 == strcmp(p_argv[1], "tomorrow"))
        {
            meat_time_single_day_range(
                i_now + meat_time_offset_days(1),
                &i_range_begin,
                &i_range_end);
        }
        else if (0 == strcmp(p_argv[1], "yesterday"))
        {
            meat_time_single_day_range(
                i_now - meat_time_offset_days(1),
                &i_range_begin,
                &i_range_end);
        }
        else if (0 == strcmp(p_argv[1], "this"))
        {
            if (i_argc > 2)
            {
                if (0 == strcmp(p_argv[2], "day"))
                {
                    meat_time_single_day_range(
                        i_now,
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(p_argv[2], "week"))
                {
                    meat_time_single_week_range(
                        i_now,
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(p_argv[2], "month"))
                {
                    meat_time_single_month_range(
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
                    meat_time_single_day_range(
                        i_now + meat_time_offset_days(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(p_argv[2], "week"))
                {
                    meat_time_single_week_range(
                        i_now + meat_time_offset_weeks(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(p_argv[2], "month"))
                {
                    meat_time_single_month_range(
                        meat_time_find_middle_of_month(i_now, 1),
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
                            meat_time_align_range_to_day(
                                i_now + meat_time_offset_days(1),
                                i_now + meat_time_offset_days(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if ((i_count > 1) && (0 == strcmp(p_argv[3], "weeks")))
                        {
                            meat_time_align_range_to_week(
                                i_now + meat_time_offset_weeks(1),
                                i_now + meat_time_offset_weeks(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if ((i_count > 1) && (0 == strcmp(p_argv[3], "months")))
                        {
                            meat_time_align_range_to_month(
                                meat_time_find_middle_of_month(i_now, 1),
                                meat_time_find_middle_of_month(i_now, i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                    }
                }
                else if (-1 != (i_wday = meat_time_which_wday(p_argv[2])))
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
        else if (0 == strcmp(p_argv[1], "last"))
        {
            if (i_argc > 2)
            {
                if (0 == strcmp(p_argv[2], "day"))
                {
                    meat_time_single_day_range(
                        i_now - meat_time_offset_days(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(p_argv[2], "week"))
                {
                    meat_time_single_week_range(
                        i_now - meat_time_offset_weeks(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(p_argv[2], "month"))
                {
                    meat_time_single_month_range(
                        meat_time_find_middle_of_month(i_now, -1),
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
                                meat_time_align_range_to_day(
                                    i_now - meat_time_offset_days(i_count),
                                    i_now - meat_time_offset_days(1),
                                    &i_range_begin,
                                    &i_range_end);
                            }
                            else if (0 == strcmp(p_argv[3], "weeks"))
                            {
                                meat_time_align_range_to_week(
                                    i_now - meat_time_offset_weeks(i_count),
                                    i_now - meat_time_offset_weeks(1),
                                    &i_range_begin,
                                    &i_range_end);
                            }
                            else if (0 == strcmp(p_argv[3], "months"))
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
                        meat_time_single_day_range(
                            i_now - meat_time_offset_days(i_count),
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
                        meat_time_single_week_range(
                            i_now - meat_time_offset_weeks(i_count),
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
                        meat_time_single_month_range(
                            meat_time_find_middle_of_month(i_now, -i_count),
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
                            meat_time_single_day_range(
                                i_now + meat_time_offset_days(i_count),
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
                            meat_time_single_week_range(
                                i_now + meat_time_offset_weeks(i_count),
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
                            meat_time_single_month_range(
                                meat_time_find_middle_of_month(i_now, i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                    }
                }
            }
        }
        else if (-1 != (i_month = meat_time_which_month(p_argv[1])))
        {
            signed long int
                i_random_day_of_month;

            if (o_time_now.i_month > i_month)
            {
                i_random_day_of_month =
                    meat_time_init_day(
                        0,
                        12,
                        11,
                        i_month,
                        o_time_now.i_year + 1);
            }
            else
            {
                i_random_day_of_month =
                    meat_time_init_day(
                        0,
                        12,
                        11,
                        i_month,
                        o_time_now.i_year);
            }

            meat_time_single_month_range(
                i_random_day_of_month,
                &i_range_begin,
                &i_range_end);
        }
        else if (-1 != (i_wday = meat_time_which_wday(p_argv[1])))
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
