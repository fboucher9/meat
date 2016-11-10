/* See LICENSE for license details. */

/*

Module: meat_chunk.c

Description:

    String of characters stored as a linked list of chunks (or parts).

*/

#include "meat_os.h"

#include "meat_list.h"

#include "meat_chunk.h"

#include "meat_heap.h"

#include "meat_ctxt.h"

/*

Function: meat_chunk_list_init

Description:

*/
void
meat_chunk_list_init(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_chunk_list * const
        p_chunk_list)
{
    (void)(
        p_ctxt);

    meat_list_init(
        &(
            p_chunk_list->o_list));

    p_chunk_list->i_total_len =
        0u;

} /* meat_chunk_list_init() */

/*

Function: meat_chunk_list_cleanup

Description:

*/
void
meat_chunk_list_cleanup(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_chunk_list * const
        p_chunk_list)
{
    /* Free all chunks */
    struct meat_list *
        p_iterator;

    p_iterator =
        p_chunk_list->o_list.p_next;

    /* For each chunk in list */
    while (
        p_iterator
        != &(
            p_chunk_list->o_list))
    {
        struct meat_list *
            p_next;

        p_next =
            p_iterator->p_next;

        /* Free a single chunk */
        meat_list_join(
            p_iterator,
            p_iterator);

        meat_heap_free(
            p_ctxt,
            p_ctxt->p_heap,
            (void *)(
                p_iterator));

        /* Continue iteration */
        p_iterator =
            p_next;

    }

    /* Reset */
    p_chunk_list->i_total_len =
        0u;

} /* meat_chunk_list_cleanup() */

/*

Function: meat_chunk_list_write

Description:

*/
void
meat_chunk_list_write(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_chunk_list * const
        p_chunk_list,
    unsigned char const
        c_data)
{
    struct meat_chunk *
        p_chunk;

    /* Is list empty */
    if (
        p_chunk_list->o_list.p_prev
        == &(
            p_chunk_list->o_list))
    {
        p_chunk =
            NULL;
    }
    else
    {
        struct meat_chunk *
            p_tmp;

        p_tmp =
            (struct meat_chunk *)(
                p_chunk_list->o_list.p_prev);

        /* Is node full */
        if (
            p_tmp->i_len >= MEAT_CHUNK_BUFFER_LENGTH)
        {
            p_chunk =
                NULL;
        }
        else
        {
            p_chunk =
                p_tmp;
        }
    }

    if (
        !p_chunk)
    {
        p_chunk =
            (struct meat_chunk *)(
                meat_heap_alloc(
                    p_ctxt,
                    p_ctxt->p_heap,
                    sizeof(
                        struct meat_chunk)));

        if (
            p_chunk)
        {
            meat_list_init(
                &(
                    p_chunk->o_list));

            p_chunk->i_len =
                0u;

            meat_list_join(
                &(
                    p_chunk->o_list),
                &(
                    p_chunk_list->o_list));
        }
    }

    if (
        p_chunk)
    {
        p_chunk->a_buf[p_chunk->i_len] = c_data;

        p_chunk->i_len ++;

        p_chunk_list->i_total_len ++;
    }

} /* meat_chunk_list_write() */

/*

Function: meat_chunk_list_read

Description:

*/
void
meat_chunk_list_read(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_chunk_list * const
        p_chunk_list,
    unsigned char * const
        p_buf,
    unsigned int const
        i_buf_len)
{
    unsigned int
        i_buf_it;

    struct meat_list *
        p_list_it;

    (void)(
        p_ctxt);

    i_buf_it =
        0u;

    p_list_it =
        p_chunk_list->o_list.p_next;

    while (
        (
            i_buf_it
            < i_buf_len)
        && (
            p_list_it !=
            &(
                p_chunk_list->o_list)))
    {
        struct meat_chunk *
            p_chunk;

        unsigned int
            i_chunk_it;

        p_chunk =
            (struct meat_chunk *)(
                p_list_it);

        i_chunk_it =
            0u;

        while (
            (
                i_buf_it
                < i_buf_len)
            && (
                i_chunk_it
                < p_chunk->i_len))
        {
            p_buf[i_buf_it] =
                p_chunk->a_buf[i_chunk_it];

            i_buf_it ++;

            i_chunk_it ++;
        }

        if (
            i_buf_it
            < i_buf_len)
        {
            p_list_it =
                p_list_it->p_next;
        }
    }

} /* meat_chunk_list_read() */

/* end-of-file: meat_chunk.c */
