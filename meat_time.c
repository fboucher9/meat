/* See LICENSE for license details. */

/*

Module: meat_time.c

Description:

*/

#include "meat_os.h"

#include "meat_time.h"

signed long int
    offset_minutes(
        int const i_minutes)
{
    return ((signed long int)(i_minutes) * 60l);
}

signed long int
    offset_hours(
        int const i_hour)
{
    return
        offset_minutes(
            i_hour * 60l);
}

signed long int
    offset_time_of_day(
        int const i_hour,
        int const i_minutes)
{
    return
        (
            offset_hours(
                i_hour)
            + offset_minutes(
                i_minutes));
}

signed long int
    offset_days(
        int const i_days)
{
    return
        offset_hours(
            i_days * 24l);
}

signed long int
    offset_weeks(
        int const i_weeks)
{
    return
        offset_days(
            i_weeks * 7);
}

signed long int
    offset_months(
        int const i_months)
{
    return
        offset_days(
            i_months * 30);

}

time_t
    init_day(
        int const
            i_minutes,
        int const
            i_hour,
        int const
            mday,
        int const
            month,
        int const
            year)
{
    struct tm
        o_descriptor;

    o_descriptor.tm_sec =
        0;

    o_descriptor.tm_min =
        i_minutes;

    o_descriptor.tm_hour =
        i_hour;

    o_descriptor.tm_mday =
        mday;

    o_descriptor.tm_mon =
        month;

    o_descriptor.tm_year =
        year;

    o_descriptor.tm_wday =
        0;

    o_descriptor.tm_yday =
        0;

    o_descriptor.tm_isdst =
        0;

    return
        mktime(
            &o_descriptor);

}

void
    get_day(
        time_t const
            base,
        struct tm * const
            po_result)
{
    struct tm const *
        po_localtime_tmp;

    po_localtime_tmp =
        localtime(
            &(
                base));

    if (
        po_localtime_tmp)
    {
        *(
            po_result) =
            *(
                po_localtime_tmp);
    }

}

time_t
    find_begin_of_day(
        time_t const
            i_now)
{
    struct tm
        o_now;

    get_day(
        i_now,
        &(
            o_now));

    return
        i_now
        - offset_time_of_day(
            o_now.tm_hour,
            o_now.tm_min);

}

time_t
    find_end_of_day(
        time_t const
            i_now)
{
    return
        find_begin_of_day(
            i_now)
        + offset_days(1);
}

time_t
    find_begin_of_week(
        time_t const
            i_now)
{
    struct tm
        o_now;

    get_day(
        i_now,
        &(
            o_now));

    return
        find_begin_of_day(
            i_now)
        - offset_days(
            o_now.tm_wday);
}

time_t
    find_end_of_week(
        time_t const
            i_now)
{
    return
        find_begin_of_week(
            i_now)
        + offset_weeks(1);

}

time_t
    find_begin_of_month(
        time_t const i_now)
{
    struct tm
        o_now;

    get_day(
        i_now,
        &(
            o_now));

    return
        i_now
        - offset_time_of_day(
            o_now.tm_hour,
            o_now.tm_min)
        - offset_days(
            o_now.tm_mday - 1);

}

time_t
    find_middle_of_month(
        time_t const
            i_now,
        int const
            i_count)
{
    time_t
        i_begin_of_month;

    i_begin_of_month =
        find_begin_of_month(
            i_now);

    /* Offset to get to middle of month */
    return
        (
            i_begin_of_month
            + offset_days(
                14)
            + offset_months(
                i_count));

}

time_t
    find_end_of_month(
        time_t const
            i_now)
{
    time_t
        i_middle_of_next_month;

    i_middle_of_next_month =
        find_middle_of_month(
            i_now,
            1);

    return
        find_begin_of_month(
            i_middle_of_next_month);

}

void
    align_range_to_day(
        time_t const
            i_begin,
        time_t const
            i_end,
        time_t * const
            pi_begin,
        time_t * const
            pi_end)
{
    *pi_begin =
        find_begin_of_day(
            i_begin);

    *pi_end =
        find_end_of_day(
            i_end);

}

void
    align_range_to_week(
        time_t const
            i_begin,
        time_t const
            i_end,
        time_t * const
            pi_begin,
        time_t * const
            pi_end)
{
    *pi_begin =
        find_begin_of_week(
            i_begin);

    *pi_end =
        find_end_of_week(
            i_end);

}

void
    align_range_to_month(
        time_t const
            i_begin,
        time_t const
            i_end,
        time_t * const
            pi_begin,
        time_t * const
            pi_end)
{
    *pi_begin =
        find_begin_of_month(
            i_begin);

    *pi_end =
        find_end_of_month(
            i_end);

}

void
    single_day_range(
        time_t const
            i_now,
        time_t * const
            pi_begin,
        time_t * const
            pi_end)
{
    align_range_to_day(
        i_now,
        i_now,
        pi_begin,
        pi_end);
}

void
    single_week_range(
        time_t const
            i_now,
        time_t * const
            pi_begin,
        time_t * const
            pi_end)
{
    align_range_to_week(
        i_now,
        i_now,
        pi_begin,
        pi_end);
}

void
    single_month_range(
        time_t i_now,
        time_t * const pi_begin,
        time_t * const pi_end)
{
    align_range_to_month(
        i_now,
        i_now,
        pi_begin,
        pi_end);

}

void
format_date(
    time_t const
        i_now,
    char * const
        p_text)
{
    char const *
        p_buf;

    p_buf =
        ctime(
            &(
                i_now));

    if (
        p_buf)
    {
        int
            i_buf_len;

        i_buf_len =
            strlen(
                p_buf);

        if (
            '\n'
            == p_buf[i_buf_len - 1])
        {
            i_buf_len --;
        }

        memcpy(
            p_text,
            p_buf,
            i_buf_len);

        p_text[i_buf_len] =
            '\000';
    }
    else
    {
        p_text[0] = '-';
        p_text[1] = '\000';
    }
}

int
which_month(
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
which_wday(
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

