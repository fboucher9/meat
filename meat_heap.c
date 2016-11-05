/* See LICENSE for license details. */

/*

Module: meat_heap.c

Description:

*/

#include "meat_os.h"

#include "meat_heap.h"

#include "meat_list.h"

#include "meat_dbg.h"

/* State for meat_heap module */
static
char
b_meat_heap_init_done = 0;

static
struct meat_list
o_meat_heap_list =
{
    &(
        o_meat_heap_list),
    &(
        o_meat_heap_list)
};

/*

Structure: meat_heap_prefix

Description:

    Header for an allocation.

*/
struct meat_heap_prefix
{
    struct meat_list
        o_list;

    void *
        a_stack[5u];

    size_t
        i_buf_len;

    char
        a_header[8u];

}; /* struct meat_heap_prefix */

/*

Structure: meat_heap_suffix

Description:

    Footer for an allocation.

*/
struct meat_heap_suffix
{
    char
        a_footer[8u];

}; /* struct meat_heap_suffix */

/*

Function: meat_heap_alloc

Description:

    Allocate 'i_buf_len' bytes of memory from application heap.  Perform
    extra features like leak detection and buffer overrun protection.

Parameters:

    size_t i_buf_len

        Number of bytes to allocate.

Returns:

    void *

        Pointer to allocated memory.

Comments:

*/
void *
meat_heap_alloc(
    size_t const
        i_buf_len)
{
    void *
        p_buf;

    if (
        b_meat_heap_init_done)
    {
        struct meat_heap_prefix *
            p_prefix;

        char *
            p_body;

        struct meat_heap_suffix *
            p_suffix;

        size_t
            i_buf_len_aligned;

        size_t
            i_total_len;

        i_buf_len_aligned =
            (size_t)(
                (
                    i_buf_len
                    + 7ul)
                - (
                    (
                        i_buf_len
                        + 7ul)
                    & 7ul));

        i_total_len =
            (size_t)(
                sizeof(struct meat_heap_prefix)
                + i_buf_len_aligned
                + sizeof(struct meat_heap_suffix));

        p_prefix =
            (struct meat_heap_prefix *)(
                malloc(
                    i_total_len));

        if (
            p_prefix)
        {
            p_body =
                (char *)(
                    p_prefix + 1);

            p_suffix =
                (struct meat_heap_suffix *)(
                    p_body + p_prefix->i_buf_len);

            meat_list_init(
                &(
                    p_prefix->o_list));

            backtrace(
                p_prefix->a_stack,
                5u);

            p_prefix->i_buf_len =
                i_buf_len_aligned;

            memset(
                p_prefix->a_header,
                0xBE,
                sizeof(p_prefix->a_header));

            memset(
                p_body,
                0xCC,
                p_prefix->i_buf_len);

            memset(
                p_suffix->a_footer,
                0xAF,
                sizeof(p_suffix->a_footer));

            meat_list_join(
                &(
                    p_prefix->o_list),
                &(
                    o_meat_heap_list));

            p_buf =
                (void *)(
                    p_body);
        }
        else
        {
            meat_dbg_break();

            p_buf =
                0;
        }
    }
    else
    {
        meat_dbg_break();

        p_buf =
            0;
    }

    return
        p_buf;

} /* meat_heap_alloc() */

/*

Function: meat_heap_free

Description:

    Free a buffer that was allocated by meat_heap_alloc.  Perform extra
    features like leak detection and buffer overrun protection.

*/
void
meat_heap_free(
    void * const
        p_buf)
{
    if (
        b_meat_heap_init_done)
    {
        struct meat_heap_prefix *
            p_prefix;

        char *
            p_body;

        struct meat_heap_suffix *
            p_suffix;

        p_prefix =
            (struct meat_heap_prefix *)(
                p_buf)
            - 1;

        p_body =
            (char *)(
                p_buf);

        p_suffix =
            (struct meat_heap_suffix *)(
                p_body
                + p_prefix->i_buf_len);

        meat_list_join(
            &(
                p_prefix->o_list),
            &(
                p_prefix->o_list));

        free(
            p_prefix);
    }
    else
    {
        meat_dbg_break();
    }

} /* meat_heap_free() */

/*

Function: meat_heap_init

Description:

    Initialize the meat_heap module.

*/
void
meat_heap_init(void)
{
    if (
        !b_meat_heap_init_done)
    {
        b_meat_heap_init_done =
            1;
    }

} /* meat_heap_init() */

/*

Function: meat_heap_cleanup

Description:

    Undo initialization of meat_heap module.

*/
void
meat_heap_cleanup(void)
{
    if (
        b_meat_heap_init_done)
    {
        if (o_meat_heap_list.p_next != &o_meat_heap_list)
        {
            struct meat_list *
                p_iterator;

            p_iterator =
                o_meat_heap_list.p_next;

            while (
                p_iterator != &o_meat_heap_list)
            {
                struct meat_heap_prefix *
                    p_prefix;

                p_prefix =
                    (struct meat_heap_prefix *)(
                        p_iterator);

                printf("*** allocation of %lu bytes ***\n", (unsigned long int)(p_prefix->i_buf_len));

                backtrace_symbols_fd(p_prefix->a_stack, 5, 1);

                p_iterator =
                    p_iterator->p_next;
            }

            meat_dbg_break();
        }

        b_meat_heap_init_done =
            0;
    }

} /* meat_heap_cleanup() */

/* end-of-file: meat_heap.c */
