/* See LICENSE for license details. */

/*

Module: meat_time.c

Description:

*/

#include "meat_os.h"

#include "meat_time.h"

/* For mktime, localtime, ctime, ... */
#include <time.h>

signed long int
    meat_time_offset_minutes(
        int const i_minutes)
{
    return
        i_minutes;

}

signed long int
    meat_time_offset_hours(
        int const i_hour)
{
    return
        meat_time_offset_minutes(
            i_hour * 60l);
}

signed long int
    meat_time_offset_time_of_day(
        int const i_hour,
        int const i_minutes)
{
    return
        (
            meat_time_offset_hours(
                i_hour)
            + meat_time_offset_minutes(
                i_minutes));
}

signed long int
    meat_time_offset_days(
        int const i_days)
{
    return
        meat_time_offset_hours(
            i_days * 24l);
}

signed long int
    meat_time_offset_weeks(
        int const i_weeks)
{
    return
        meat_time_offset_days(
            i_weeks * 7);
}

signed long int
    meat_time_offset_months(
        int const i_months)
{
    return
        meat_time_offset_days(
            i_months * 30);

}

signed long int
    meat_time_init_day(
        struct meat_time_info const * const
            p_info)
{
    struct tm
        o_descriptor;

    o_descriptor.tm_sec =
        0;

    o_descriptor.tm_min =
        p_info->i_minute;

    o_descriptor.tm_hour =
        p_info->i_hour;

    o_descriptor.tm_mday =
        p_info->i_day_of_month;

    o_descriptor.tm_mon =
        p_info->i_month;

    o_descriptor.tm_year =
        p_info->i_year;

    o_descriptor.tm_wday =
        0;

    o_descriptor.tm_yday =
        0;

    o_descriptor.tm_isdst =
        0;

    return
        (signed long int)(
            mktime(
                &o_descriptor) / 60l);

}

void
    meat_time_get_day(
        signed long int const
            base,
        struct meat_time_info * const
            p_result)
{
    struct tm const *
        p_tmp;

    time_t
        i_posix_time;

    i_posix_time =
        (time_t)(
            base)
        * 60l;

    p_tmp =
        localtime(
            &(
                i_posix_time));

    if (
        p_tmp)
    {
        p_result->i_minute =
            p_tmp->tm_min;

        p_result->i_hour =
            p_tmp->tm_hour;

        p_result->i_day_of_month =
            p_tmp->tm_mday;

        p_result->i_day_of_week =
            p_tmp->tm_wday;

        p_result->i_month =
            p_tmp->tm_mon;

        p_result->i_year =
            p_tmp->tm_year;
    }

}

signed long int
    meat_time_find_begin_of_day(
        signed long int const
            i_now)
{
    struct meat_time_info
        o_now;

    meat_time_get_day(
        i_now,
        &(
            o_now));

    return
        i_now
        - meat_time_offset_time_of_day(
            o_now.i_hour,
            o_now.i_minute);

}

signed long int
    meat_time_find_end_of_day(
        signed long int const
            i_now)
{
    return
        meat_time_find_begin_of_day(
            i_now)
        + meat_time_offset_days(1);
}

signed long int
    meat_time_find_begin_of_week(
        signed long int const
            i_now)
{
    struct meat_time_info
        o_now;

    meat_time_get_day(
        i_now,
        &(
            o_now));

    return
        meat_time_find_begin_of_day(
            i_now)
        - meat_time_offset_days(
            o_now.i_day_of_week);

}

signed long int
    meat_time_find_end_of_week(
        signed long int const
            i_now)
{
    return
        meat_time_find_begin_of_week(
            i_now)
        + meat_time_offset_weeks(1);

}

signed long int
    meat_time_find_begin_of_month(
        signed long int const i_now)
{
    struct meat_time_info
        o_now;

    meat_time_get_day(
        i_now,
        &(
            o_now));

    return
        i_now
        - meat_time_offset_time_of_day(
            o_now.i_hour,
            o_now.i_minute)
        - meat_time_offset_days(
            o_now.i_day_of_month - 1);

}

signed long int
    meat_time_find_middle_of_month(
        signed long int const
            i_now,
        int const
            i_count)
{
    signed long int
        i_begin_of_month;

    i_begin_of_month =
        meat_time_find_begin_of_month(
            i_now);

    /* Offset to get to middle of month */
    return
        (
            i_begin_of_month
            + meat_time_offset_days(
                14)
            + meat_time_offset_months(
                i_count));

}

signed long int
    meat_time_find_end_of_month(
        signed long int const
            i_now)
{
    signed long int
        i_middle_of_next_month;

    i_middle_of_next_month =
        meat_time_find_middle_of_month(
            i_now,
            1);

    return
        meat_time_find_begin_of_month(
            i_middle_of_next_month);

}

void
    meat_time_align_range_to_day(
        signed long int const
            i_begin,
        signed long int const
            i_end,
        signed long int * const
            pi_begin,
        signed long int * const
            pi_end)
{
    *pi_begin =
        meat_time_find_begin_of_day(
            i_begin);

    *pi_end =
        meat_time_find_end_of_day(
            i_end);

}

void
    meat_time_align_range_to_week(
        signed long int const
            i_begin,
        signed long int const
            i_end,
        signed long int * const
            pi_begin,
        signed long int * const
            pi_end)
{
    *pi_begin =
        meat_time_find_begin_of_week(
            i_begin);

    *pi_end =
        meat_time_find_end_of_week(
            i_end);

}

void
    meat_time_align_range_to_month(
        signed long int const
            i_begin,
        signed long int const
            i_end,
        signed long int * const
            pi_begin,
        signed long int * const
            pi_end)
{
    *pi_begin =
        meat_time_find_begin_of_month(
            i_begin);

    *pi_end =
        meat_time_find_end_of_month(
            i_end);

}

void
    meat_time_single_day_range(
        signed long int const
            i_now,
        signed long int * const
            pi_begin,
        signed long int * const
            pi_end)
{
    meat_time_align_range_to_day(
        i_now,
        i_now,
        pi_begin,
        pi_end);
}

void
    meat_time_single_week_range(
        signed long int const
            i_now,
        signed long int * const
            pi_begin,
        signed long int * const
            pi_end)
{
    meat_time_align_range_to_week(
        i_now,
        i_now,
        pi_begin,
        pi_end);
}

void
    meat_time_single_month_range(
        signed long int i_now,
        signed long int * const pi_begin,
        signed long int * const pi_end)
{
    meat_time_align_range_to_month(
        i_now,
        i_now,
        pi_begin,
        pi_end);

}

size_t
meat_time_format_date(
    signed long int const
        i_now,
    char * const
        p_text,
    size_t const
        i_text_max_len)
{
    size_t
        i_text_len;

    char const *
        p_buf;

    time_t
        i_posix_time;

    i_posix_time =
        (time_t)(
            i_now)
        * 60l;

    p_buf =
        ctime(
            &(
                i_posix_time));

    if (
        p_buf)
    {
        i_text_len =
            (unsigned int)(
                strlen(
                    p_buf));

        if (
            i_text_len > i_text_max_len)
        {
            i_text_len =
                i_text_max_len
                - 1;
        }

        if (
            (
                i_text_len
                > 0)
            && (
                '\n'
                == p_buf[i_text_len - 1]))
        {
            i_text_len --;
        }

        memcpy(
            p_text,
            p_buf,
            i_text_len);

        p_text[i_text_len] =
            '\000';
    }
    else
    {
        p_text[0] = '\000';

        i_text_len = 0;
    }

    return
        i_text_len;

}

int
meat_time_which_month(
    char const * const
        p_arg)
{
    static char const * const a_ref_month[12] =
    {
        "jan",
        "feb",
        "mar",
        "apr",
        "may",
        "jun",
        "jul",
        "aug",
        "sep",
        "oct",
        "nov",
        "dec"
    };

    int
        i_month;

    char
        b_found;

    i_month =
        0;

    b_found =
        0;

    while (
        !b_found && (i_month < 12))
    {
        if (0 == strcmp(p_arg, a_ref_month[i_month]))
        {
            b_found = 1;
        }
        else
        {
            i_month ++;
        }
    }

    if (
        !b_found)
    {
        i_month =
            -1;
    }

    return
        i_month;

}

int
meat_time_which_wday(
    char const * const
        p_arg)
{
    static char const * const a_ref_wday[7] =
    {
        "sun",
        "mon",
        "tue",
        "wed",
        "thu",
        "fri",
        "sat"
    };

    int
        i_wday;

    char
        b_found;

    i_wday =
        0;

    b_found =
        0;

    while (
        !b_found
        && (
            i_wday
            < 7))
    {
        if (
            0
            == strcmp(
                p_arg,
                a_ref_wday[i_wday]))
        {
            b_found =
                1;
        }
        else
        {
            i_wday ++;
        }
    }

    if (
        !b_found)
    {
        i_wday =
            -1;
    }

    return
        i_wday;

}

signed long int
meat_time_now(void)
{
    return
        (signed long int)(
            time(
                NULL) / 60l);

}

/* end-of-file: meat_time.c */
