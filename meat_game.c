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
char
    process_line(
        struct meat_game_list * const
            p_game_list,
        char * a_line)
{
    char
        b_continue;

    struct meat_game *
        p_game;

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
char
    process_file(
        struct meat_game_list * const
            p_game_list,
        FILE * const
            p_input)
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
            a_line[255u] =
                '\000';

            b_continue =
                process_line(
                    p_game_list,
                    a_line);

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
    FILE * const
        p_input)
{
    meat_list_init(
        &(
            p_game_list->o_list));

    return
        process_file(
            p_game_list,
            p_input);

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
