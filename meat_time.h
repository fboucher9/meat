/* See LICENSE for license details. */

/*

Module: meat_time.h

Description:

*/

/* Header file dependency */
#if !defined(INC_MEAT_OS_H)
#error include meat_os.h first
#endif /* #if !defined(INC_MEAT_OS_H) */

#if defined(INC_MEAT_TIME_H)
#error include meat_time.h once
#endif /* #if defined(INC_MEAT_TIME_H) */

struct meat_time_info
{
    int
        i_minute;

    int
        i_hour;

    int
        i_day_of_month;

    int
        i_day_of_week;

    int
        i_month;

    int
        i_year;

}; /* struct meat_time_info */

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_offset_hours(
        int const i_hour);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_offset_minutes(
        int const i_minutes);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_offset_time_of_day(
        int const i_hour,
        int const i_minutes);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_offset_days(
        int const i_days);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_offset_weeks(
        int const i_weeks);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_offset_months(
        int const i_months);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_init_day(
        struct meat_time_info const * const
            p_info);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
    meat_time_get_day(
        signed long int const
            base,
        struct meat_time_info * const
            p_result);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_find_begin_of_day(
        signed long int const
            i_now);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_find_end_of_day(
        signed long int const
            i_now);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_find_begin_of_week(
        signed long int const
            i_now);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_find_end_of_week(
        signed long int const
            i_now);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_find_begin_of_month(
        signed long int const i_now);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_find_middle_of_month(
        signed long int const
            i_now,
        int const
            i_count);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_time_find_end_of_month(
        signed long int const
            i_now);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
    meat_time_align_range_to_day(
        signed long int const
            i_begin,
        signed long int const
            i_end,
        signed long int * const
            pi_begin,
        signed long int * const
            pi_end);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
    meat_time_align_range_to_week(
        signed long int const
            i_begin,
        signed long int const
            i_end,
        signed long int * const
            pi_begin,
        signed long int * const
            pi_end);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
    meat_time_align_range_to_month(
        signed long int const
            i_begin,
        signed long int const
            i_end,
        signed long int * const
            pi_begin,
        signed long int * const
            pi_end);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
    meat_time_single_day_range(
        signed long int const
            i_now,
        signed long int * const
            pi_begin,
        signed long int * const
            pi_end);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
    meat_time_single_week_range(
        signed long int const
            i_now,
        signed long int * const
            pi_begin,
        signed long int * const
            pi_end);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
    meat_time_single_month_range(
        signed long int
            i_now,
        signed long int * const
            pi_begin,
        signed long int * const
            pi_end);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
size_t
meat_time_format_date(
    signed long int const
        i_now,
    char * const
        p_text,
    size_t const
        i_text_max_len);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
int
meat_time_which_month(
    char const * const
        p_arg);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
int
meat_time_which_wday(
    char const * const
        p_arg);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
meat_time_now(void);

/* end-of-file: meat_time.h */
