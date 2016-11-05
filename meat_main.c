
#include "meat_os.h"

#include "meat_list.h"

#include "meat_time.h"

#include "meat_main.h"

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
struct meat_list
o_game_list;

struct meat_game
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

    char const *
        away_team;

    char const *
        home_team;

    char const *
        remarks;

};

static
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
            ' ' == p_buf[i_buf_len - 1]))
    {
        p_buf[i_buf_len - 1] = '\000';

        i_buf_len --;
    }

    return p_buf;
}

static
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

static
char *
dup_str(
    char const * const
        p_buf)
{
    int
        i_buf_len;

    char *
        p_buf_copy;

    i_buf_len =
        strlen(
            p_buf);

    p_buf_copy =
        malloc(
            i_buf_len + 1);

    if (
        p_buf_copy)
    {
        strcpy(
            p_buf_copy,
            p_buf);
    }

    return
        p_buf_copy;

}

/* Load games from input file */
static
void
load_games(
    FILE * p_input)
{
    char *
        p_result;

    char *
        p_token;

    int
        i_token;

    char
        b_continue;

    char
        a_line[256u];

    o_game_list.p_next = &o_game_list;

    o_game_list.p_prev = &o_game_list;

    b_continue =
        1;

    while (
        b_continue)
    {
        struct meat_game *
            p_game =
            (struct meat_game *)(
                malloc(
                    sizeof(
                        struct meat_game)));

        if (
            p_game)
        {
            p_game->year = 0;

            p_game->month = 0;

            p_game->day = 0;

            p_game->hour = 0;

            p_game->minute = 0;

            p_game->away_team = NULL;

            p_game->home_team = NULL;

            p_game->remarks = NULL;

            p_result =
                fgets(
                    a_line,
                    sizeof(
                        a_line),
                    p_input);

            if (
                p_result)
            {
                a_line[255u] =
                    '\000';

                p_token =
                    strtok(
                        a_line,
                        "|:/\n");

                i_token =
                    0;

                while (
                    p_token &&
                    (i_token < 8))
                {
                    switch (
                        i_token)
                    {
                        case 0:
                            sscanf(p_token, "%u", &p_game->year);
                            break;

                        case 1:
                            sscanf(p_token, "%u", &p_game->month);
                            break;

                        case 2:
                            sscanf(p_token, "%u", &p_game->day);
                            break;

                        case 3:
                            sscanf(p_token, "%u", &p_game->hour);
                            break;

                        case 4:
                            sscanf(p_token, "%u", &p_game->minute);
                            break;

                        case 5:
                            p_game->away_team = strip_trailing_spaces(dup_str(skip_leading_spaces(p_token)));
                            break;

                        case 6:
                            p_game->home_team = strip_trailing_spaces(dup_str(skip_leading_spaces(p_token)));
                            break;

                        case 7:
                            p_game->remarks = strip_trailing_spaces(dup_str(skip_leading_spaces(p_token)));
                            break;
                    }

                    p_token =
                        strtok(
                            NULL,
                            "|:/\n");

                    i_token ++;
                }

                {
                    struct meat_list * p_node = meat_list_alloc(p_game);

                    meat_list_join(p_node, &o_game_list);
                }
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
    struct meat_list * iterator;

    iterator = o_game_list.p_next;

    while (iterator != &o_game_list)
    {
        struct meat_game const * p_game = (struct meat_game const *)(iterator->p_data);

        printf("%4d/%02d/%02d %2d:%02d {%s} {%s} {%s}\n",
            p_game->year,
            p_game->month,
            p_game->day,
            p_game->hour,
            p_game->minute,
            p_game->away_team,
            p_game->home_team,
            p_game->remarks);

        iterator = iterator->p_next;
    }
#endif /* debug */
}


static
void
process_command(
    unsigned int const
        argc,
    char const * const * const
        argv,
    time_t * const
        pi_begin,
    time_t * const
        pi_end)
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
        argc > 1)
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
        if (0 == strcmp(argv[1], "today"))
        {
            single_day_range(
                i_now,
                &i_range_begin,
                &i_range_end);
        }
        else if (0 == strcmp(argv[1], "tomorrow"))
        {
            single_day_range(
                i_now + offset_days(1),
                &i_range_begin,
                &i_range_end);
        }
        else if (0 == strcmp(argv[1], "yesterday"))
        {
            single_day_range(
                i_now - offset_days(1),
                &i_range_begin,
                &i_range_end);
        }
        else if (0 == strcmp(argv[1], "this"))
        {
            if (argc > 2)
            {
                if (0 == strcmp(argv[2], "day"))
                {
                    single_day_range(
                        i_now,
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(argv[2], "week"))
                {
                    single_week_range(
                        i_now,
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(argv[2], "month"))
                {
                    single_month_range(
                        i_now,
                        &i_range_begin,
                        &i_range_end);
                }
            }
        }
        else if (0 == strcmp(argv[1], "next"))
        {
            if (argc > 2)
            {
                if (0 == strcmp(argv[2], "day"))
                {
                    single_day_range(
                        i_now + offset_days(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(argv[2], "week"))
                {
                    single_week_range(
                        i_now + offset_weeks(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(argv[2], "month"))
                {
                    single_month_range(
                        find_middle_of_month(i_now, 1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (('0' <= argv[2][0]) && ('9' >= argv[2][0]))
                {
                    i_count = 1;
                    sscanf(argv[2], "%d", &i_count);
                    if (argc > 3)
                    {
                        if ((i_count > 1) && (0 == strcmp(argv[3], "days")))
                        {
                            align_range_to_day(
                                i_now + offset_days(1),
                                i_now + offset_days(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if ((i_count > 1) && (0 == strcmp(argv[3], "weeks")))
                        {
                            align_range_to_week(
                                i_now + offset_weeks(1),
                                i_now + offset_weeks(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if ((i_count > 1) && (0 == strcmp(argv[3], "months")))
                        {
                            align_range_to_month(
                                find_middle_of_month(i_now, 1),
                                find_middle_of_month(i_now, i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                    }
                }
                else if (-1 != (i_wday = which_wday(argv[2])))
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
        else if (0 == strcmp(argv[1], "last"))
        {
            if (argc > 2)
            {
                if (0 == strcmp(argv[2], "day"))
                {
                    single_day_range(
                        i_now - offset_days(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(argv[2], "week"))
                {
                    single_week_range(
                        i_now - offset_weeks(1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (0 == strcmp(argv[2], "month"))
                {
                    single_month_range(
                        find_middle_of_month(i_now, -1),
                        &i_range_begin,
                        &i_range_end);
                }
                else if (('0' <= argv[2][0]) && ('9' >= argv[2][0]))
                {
                    i_count = 1;
                    sscanf(argv[2], "%d", &i_count);
                    if (argc > 3)
                    {
                        if (i_count > 1)
                        {
                            if (0 == strcmp(argv[3], "days"))
                            {
                                align_range_to_day(
                                    i_now - offset_days(i_count),
                                    i_now - offset_days(1),
                                    &i_range_begin,
                                    &i_range_end);
                            }
                            else if (0 == strcmp(argv[3], "weeks"))
                            {
                                align_range_to_week(
                                    i_now - offset_weeks(i_count),
                                    i_now - offset_weeks(1),
                                    &i_range_begin,
                                    &i_range_end);
                            }
                            else if (0 == strcmp(argv[3], "months"))
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
        else if (('0' <= argv[1][0]) && ('9' >= argv[1][0]))
        {
            /* */
            i_count = 1;
            sscanf(argv[1], "%d", &i_count);
            if (argc > 3)
            {
                if (0 == strcmp(argv[3], "ago"))
                {
                    if (
                        (
                            (i_count > 1)
                            && (0 == strcmp(argv[2], "days")))
                        || (
                            (i_count == 1)
                            && (0 == strcmp(argv[2], "day"))))
                    {
                        single_day_range(
                            i_now - offset_days(i_count),
                            &i_range_begin,
                            &i_range_end);
                    }
                    else if (
                        (
                            (i_count > 1)
                            && (0 == strcmp(argv[2], "weeks")))
                        || (
                            (i_count == 1)
                            && (0 == strcmp(argv[2], "week"))))
                    {
                        single_week_range(
                            i_now - offset_weeks(i_count),
                            &i_range_begin,
                            &i_range_end);
                    }
                    else if (
                        (
                            (i_count > 1)
                            && (0 == strcmp(argv[2], "months")))
                        || (
                            (i_count == 1)
                            && (0 == strcmp(argv[2], "month"))))
                    {
                        single_month_range(
                            find_middle_of_month(i_now, -i_count),
                            &i_range_begin,
                            &i_range_end);
                    }
                }
            }
        }
        else if (0 == strcmp(argv[1], "in"))
        {
            if (argc > 2)
            {
                if (('0' <= argv[2][0]) && ('9' >= argv[2][0]))
                {
                    i_count = 1;
                    sscanf(argv[2], "%d", &i_count);
                    if (argc > 3)
                    {
                        if (
                            (
                                (i_count > 1)
                                && (0 == strcmp(argv[3], "days")))
                            || (
                                (i_count == 1)
                                && (0 == strcmp(argv[3], "day"))))
                        {
                            single_day_range(
                                i_now + offset_days(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if (
                            (
                                (i_count > 1)
                                && (0 == strcmp(argv[3], "weeks")))
                            || (
                                (i_count == 1)
                                && (0 == strcmp(argv[3], "week"))))
                        {
                            single_week_range(
                                i_now + offset_weeks(i_count),
                                &i_range_begin,
                                &i_range_end);
                        }
                        else if (
                            (
                                (i_count > 1)
                                && (0 == strcmp(argv[3], "months")))
                            || (
                                (i_count == 1)
                                && (0 == strcmp(argv[3], "month"))))
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
        else if (-1 != (i_month = which_month(argv[1])))
        {
            time_t
                i_random_day_of_month;

            if (o_time_now.tm_mon > i_month)
            {
                i_random_day_of_month =
                    init_day(
                        0,
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
        else if (-1 != (i_wday = which_wday(argv[1])))
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

    *pi_begin =
        i_range_begin;

    *pi_end =
        i_range_end;

}

int
    meat_main(
        unsigned int const
            argc,
        char const * const * const
            argv)
{
    time_t
        i_range_begin;

    time_t
        i_range_end;

    process_command(
        argc,
        argv,
        &(
            i_range_begin),
        &(
            i_range_end));

    if (
        i_range_end
        > i_range_begin)
    {
        i_range_end -= 10;

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
                i_range_begin,
                ac_range_begin);

            format_date(
                i_range_end,
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

                time_t
                    i_game_time;

                p_game =
                    (struct meat_game const *)(
                        iterator->p_data);

                i_game_time =
                    init_day(
                        0,
                        p_game->minute,
                        p_game->hour,
                        p_game->day,
                        p_game->month - 1,
                        p_game->year - 1900);

                if (
                    (
                        i_game_time
                        >= i_range_begin)
                    && (
                        i_game_time
                        <= i_range_end))
                {
                    char ac_game_time[64u];

                    format_date(
                        i_game_time,
                        ac_game_time);

                    printf("%-26s | %14s vs. %-14s | %s\n",
                        ac_game_time,
                        p_game->away_team,
                        p_game->home_team,
                        p_game->remarks);
                }

                iterator = iterator->p_next;
            }
        }
    }
    else
    {
        printf("wha?\n");
    }

    return 0;

} /* meat_main() */

/* end-of-file: meat_main.c */
