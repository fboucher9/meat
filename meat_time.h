/* See LICENSE for license details. */

/*

Module: meat_time.h

Description:

*/

signed long int
    offset_seconds(
        int const i_seconds);

signed long int
    offset_hours(
        int const i_hour);

signed long int
    offset_minutes(
        int const i_minutes);

signed long int
    offset_hour_min_sec(
        int const i_hour,
        int const i_minutes,
        int const i_seconds);

signed long int
    offset_days(
        int const i_days);

signed long int
    offset_weeks(
        int const i_weeks);

signed long int
    offset_months(
        int const i_months);

time_t
    init_day(
        int const
            i_seconds,
        int const
            i_minutes,
        int const
            i_hour,
        int const
            mday,
        int const
            month,
        int const
            year);

void
    get_day(
        time_t const
            base,
        struct tm * const
            po_result);

time_t
    find_begin_of_day(
        time_t const
            i_now);

time_t
    find_end_of_day(
        time_t const
            i_now);

time_t
    find_begin_of_week(
        time_t const
            i_now);

time_t
    find_end_of_week(
        time_t const
            i_now);

time_t
    find_begin_of_month(
        time_t const i_now);

time_t
    find_middle_of_month(
        time_t const
            i_now,
        int const
            i_count);

time_t
    find_end_of_month(
        time_t const
            i_now);

void
    align_range_to_day(
        time_t const
            i_begin,
        time_t const
            i_end,
        time_t * const
            pi_begin,
        time_t * const
            pi_end);

void
    align_range_to_week(
        time_t const
            i_begin,
        time_t const
            i_end,
        time_t * const
            pi_begin,
        time_t * const
            pi_end);

void
    align_range_to_month(
        time_t const
            i_begin,
        time_t const
            i_end,
        time_t * const
            pi_begin,
        time_t * const
            pi_end);

void
    single_day_range(
        time_t const
            i_now,
        time_t * const
            pi_begin,
        time_t * const
            pi_end);

void
    single_week_range(
        time_t const
            i_now,
        time_t * const
            pi_begin,
        time_t * const
            pi_end);

void
    single_month_range(
        time_t i_now,
        time_t * const pi_begin,
        time_t * const pi_end);

void
format_date(
    time_t const
        i_now,
    char * const
        p_text);

int
which_month(
    char const * const
        p_arg);

int
which_wday(
    char const * const
        p_arg);

/* end-of-file: meat_time.h */
