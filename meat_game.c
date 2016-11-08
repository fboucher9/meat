/* See LICENSE for license details. */

/*

Module: meat_game.c

Description:

    Database of games, events or television shows.

*/

#include "meat_os.h"

#include "meat_list.h"

#include "meat_game.h"

#include "meat_heap.h"

#include "meat_time.h"

#include "meat_file.h"

static
char
    process_line(
        struct meat_game_list * const
            p_game_list,
        char * const
            a_line,
        size_t const
            i_line_len)
{
    char
        b_continue;

    struct meat_game *
        p_game;

    int
        i_offset_end;

    p_game =
        (struct meat_game *)(
            meat_heap_alloc(
                sizeof(
                    struct meat_game)));

    if (
        p_game)
    {
        meat_list_init(
            &(
                p_game->o_list));

        p_game->i_game_time = 0;

        p_game->a_remarks[0u] = '\000';

        {
            struct meat_time_info
                o_game_time;

            int
                i_offset;

            size_t
                i_remarks_iterator;

            sscanf(
                a_line,
                "%d%d%d%d%d%n",
                &(
                    o_game_time.i_year),
                &(
                    o_game_time.i_month),
                &(
                    o_game_time.i_day_of_month),
                &(
                    o_game_time.i_hour),
                &(
                    o_game_time.i_minute),
                &(
                    i_offset));

            o_game_time.i_year -= 1900;

            o_game_time.i_month --;

            p_game->i_game_time =
                meat_time_init_day(
                    &(
                        o_game_time));

            while (
                (
                    (size_t)(i_offset) < i_line_len)
                && (
                    ' ' == a_line[i_offset]))
            {
                i_offset ++;
            }

            i_offset_end =
                i_line_len;

            while (
                (
                    i_offset_end > i_offset)
                && (
                    (
                        ' ' == a_line[i_offset_end - 1])
                    || (
                        '\n' == a_line[i_offset_end - 1])))
            {
                i_offset_end --;
            }

            i_remarks_iterator =
                0;

            while (
                i_offset < i_offset_end)
            {
                if (
                    i_remarks_iterator < (sizeof(p_game->a_remarks) - 1))
                {
                    p_game->a_remarks[i_remarks_iterator] =
                        a_line[i_offset];

                    i_remarks_iterator ++;
                }

                i_offset ++;
            }

            p_game->a_remarks[i_remarks_iterator] = '\000';
        }

        meat_list_join(
            &(
                p_game->o_list),
            &(
                p_game_list->o_list));

        b_continue =
            1;
    }
    else
    {
        b_continue =
            0;
    }

    return
        b_continue;

} /* process_line() */

static
int
    read_line(
        struct meat_file * const
            p_file,
        char * const
            p_buf,
        size_t const
            i_buf_len)
{
    char
        b_end_of_file;

    char
        b_end_of_line;

    int
        i_index;

    i_index =
        0;

    b_end_of_line =
        0;

    b_end_of_file =
        0;

    while (
        !b_end_of_file
        && !b_end_of_line)
    {
        int
            i_char;

        i_char =
            meat_file_read_char(
                p_file);

        if (
            i_char >= 0)
        {
            if (
                '\n' == i_char)
            {
                b_end_of_line =
                    1;

                p_buf[i_index] = '\000';
            }
            else
            {
                if (
                    (size_t)(i_index) < (i_buf_len - 1))
                {
                    p_buf[i_index] =
                        (char)(
                            i_char);

                    i_index ++;
                }
            }
        }
        else
        {
            b_end_of_file =
                1;

            p_buf[i_index] = '\000';

            if (0 == i_index)
            {
                i_index = -1;
            }
        }
    }

    return
        i_index;

} /* read_line() */

static
char
    process_file(
        struct meat_game_list * const
            p_game_list,
        struct meat_file * const
            p_file)
{
    char
        b_continue;

    char
        a_line[256u];

    b_continue =
        1;

    while (
        b_continue)
    {
        int
            i_line_len;

        i_line_len =
            read_line(
                p_file,
                a_line,
                sizeof(
                    a_line));

        if (
            i_line_len >= 0)
        {
            b_continue =
                process_line(
                    p_game_list,
                    a_line,
                    (size_t)(i_line_len));

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

        iterator = p_game_list->p_next;

        while (iterator != p_game_list)
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

    return
        1;

} /* process_file() */

/* Load games from input file */
char
meat_game_list_init(
    struct meat_game_list * const
        p_game_list,
    struct meat_file * const
        p_file)
{
    meat_list_init(
        &(
            p_game_list->o_list));

    return
        process_file(
            p_game_list,
            p_file);

} /* meat_game_list_init() */

void
meat_game_list_cleanup(
    struct meat_game_list * const
        p_game_list)
{
    /* Free all of the games */
    struct meat_list *
        p_iterator;

    struct meat_list *
        p_next;

    struct meat_game *
        p_game;

    p_iterator =
        p_game_list->o_list.p_next;

    while (
        p_iterator
        != &(
            p_game_list->o_list))
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

} /* meat_game_list_cleanup() */

struct meat_game_list_iterate_context
{
    void (* p_callback)(
        void * const
            p_context,
        struct meat_game * const
            p_game);

    void *
        p_context;

}; /* struct meat_game_list_iterate_context */

static
void
meat_game_list_iterate_callback(
    void * const
        p_context,
    struct meat_list * const
        p_list)
{
    struct meat_game_list_iterate_context *
        p_game_list_iterate_context;

    struct meat_game *
        p_game;

    p_game_list_iterate_context =
        (struct meat_game_list_iterate_context *)(
            p_context);

    p_game =
        (struct meat_game *)(
            p_list);

    (*p_game_list_iterate_context->p_callback)(
        p_game_list_iterate_context->p_context,
        p_game);

} /* meat_game_list_iterate_callback() */

void
meat_game_list_iterate(
    struct meat_game_list * const
        p_game_list,
    void (* p_callback)(
        void * const
            p_context,
        struct meat_game * const
            p_game),
    void * const
        p_context)
{
    struct meat_game_list_iterate_context
        o_game_list_iterate_context;

    o_game_list_iterate_context.p_callback =
        p_callback;

    o_game_list_iterate_context.p_context =
        p_context;

    meat_list_iterate(
        &(
            p_game_list->o_list),
        &(
            meat_game_list_iterate_callback),
        &(
            o_game_list_iterate_context));

} /* meat_game_list_iterate() */

/* end-of-file: meat_game.c */
