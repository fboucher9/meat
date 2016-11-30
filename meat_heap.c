/* See LICENSE for license details. */

/*

Module: meat_heap.c

Description:

*/

#include "meat_os.h"

#include "meat_cfg.h"

#include "meat_heap.h"

#include "meat_list.h"

#if defined(MEAT_CFG_DBG)
#include "meat_dbg.h"
#endif /* #if defined(MEAT_CFG_DBG) */

#if defined(MEAT_CFG_LEAK)
#include "meat_trace.h"
#endif /* #if defined(MEAT_CFG_LEAK) */

#include "meat_ctxt.h"

/* For malloc and free, ... */
#include <stdlib.h>

/* For printf */
#if defined(MEAT_CFG_LEAK)
#include <stdio.h>
#endif /* #if defined(MEAT_CFG_LEAK) */

#if defined(MEAT_CFG_LEAK)

static
struct meat_list
o_meat_heap_list =
{
    &(
        o_meat_heap_list),
    &(
        o_meat_heap_list)
};

/* Value used to sign the header of each allocation */
#define MEAT_HEAP_HEADER_SIGNATURE 0xBEu

/* Value used to sign the footer of each allocation */
#define MEAT_HEAP_FOOTER_SIGNATURE 0xAFu

/* Value used to initialize body of allocation */
#define MEAT_HEAP_BODY_CREATED 0xCCu

/* Value used to uninitialize body of allocation */
#define MEAT_HEAP_BODY_DESTROYED 0xCDu

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

    unsigned char
        a_header[8u];

}; /* struct meat_heap_prefix */

/*

Structure: meat_heap_suffix

Description:

    Footer for an allocation.

*/
struct meat_heap_suffix
{
    unsigned char
        a_footer[8u];

}; /* struct meat_heap_suffix */

static
void
fill_char_array(
    unsigned char * const
        p_char_array,
    unsigned char const
        i_fill_value,
    size_t
        i_char_array_len)
{
    size_t
        i_array_iterator;

    for (
        i_array_iterator =
            0u;
        (
            i_array_iterator
            < i_char_array_len);
        i_array_iterator ++)
    {
        p_char_array[i_array_iterator] = i_fill_value;
    }

} /* fill_char_array() */

#endif /* #if defined(MEAT_CFG_LEAK) */

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
    struct meat_ctxt * const
        p_ctxt,
    struct meat_heap * const
        p_heap,
    size_t const
        i_buf_len)
{
    void *
        p_buf;

    if (
        p_heap->b_init)
    {
#if defined(MEAT_CFG_LEAK)
        struct meat_heap_prefix *
            p_prefix;

        unsigned char *
            p_body;

        struct meat_heap_suffix *
            p_suffix;

        size_t
            i_total_len;

        i_total_len =
            (size_t)(
                sizeof(struct meat_heap_prefix)
                + i_buf_len
                + sizeof(struct meat_heap_suffix));

        p_prefix =
            (struct meat_heap_prefix *)(
                malloc(
                    i_total_len));

        if (
            p_prefix)
        {
            meat_list_init(
                &(
                    p_prefix->o_list));

            meat_trace_capture(
                p_ctxt,
                p_ctxt->p_trace,
                p_prefix->a_stack,
                5u);

            p_prefix->i_buf_len =
                i_buf_len;

            fill_char_array(
                p_prefix->a_header,
                MEAT_HEAP_HEADER_SIGNATURE,
                sizeof(p_prefix->a_header));

            p_body =
                (unsigned char *)(
                    p_prefix + 1);

            fill_char_array(
                p_body,
                MEAT_HEAP_BODY_CREATED,
                (size_t)(
                    p_prefix->i_buf_len));

            p_suffix =
                (struct meat_heap_suffix *)(
                    p_body + p_prefix->i_buf_len);

            fill_char_array(
                p_suffix->a_footer,
                MEAT_HEAP_FOOTER_SIGNATURE,
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
#if defined(MEAT_CFG_DBG)
            meat_dbg_break(
                p_ctxt,
                p_ctxt->p_dbg);
#endif /* #if defined(MEAT_CFG_DBG) */

            p_buf =
                0;
        }
#else /* #if defined(MEAT_CFG_LEAK) */
        (void)(
            p_ctxt);

        p_buf =
            malloc(
                i_buf_len);
#endif /* #if defined(MEAT_CFG_LEAK) */
    }
    else
    {
#if defined(MEAT_CFG_DBG)
        meat_dbg_break(
            p_ctxt,
            p_ctxt->p_dbg);
#endif /* #if defined(MEAT_CFG_DBG) */

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
    struct meat_ctxt * const
        p_ctxt,
    struct meat_heap * const
        p_heap,
    void * const
        p_buf)
{
    (void)(
        p_ctxt);

    if (
        p_heap->b_init)
    {
#if defined(MEAT_CFG_LEAK)
        struct meat_heap_prefix *
            p_prefix;

        unsigned char *
            p_body;

        struct meat_heap_suffix *
            p_suffix;

        p_prefix =
            (struct meat_heap_prefix *)(
                p_buf)
            - 1;

        p_body =
            (unsigned char *)(
                p_buf);

        p_suffix =
            (struct meat_heap_suffix *)(
                p_body
                + p_prefix->i_buf_len);

        {
            unsigned int
                i;

            for (
                i = 0;
                i < 8u;
                i ++)
            {
                if (
                    (
                        MEAT_HEAP_HEADER_SIGNATURE
                        != p_prefix->a_header[i])
                    || (
                        MEAT_HEAP_FOOTER_SIGNATURE
                        != p_suffix->a_footer[i]))
                {
#if defined(MEAT_CFG_DBG)
                    meat_dbg_break(
                        p_ctxt,
                        p_ctxt->p_dbg);
#endif /* #if defined(MEAT_CFG_DBG) */

                    break;
                }
            }
        }

        fill_char_array(
            p_body,
            MEAT_HEAP_BODY_DESTROYED,
            p_prefix->i_buf_len);

        meat_list_join(
            &(
                p_prefix->o_list),
            &(
                p_prefix->o_list));

        free(
            p_prefix);
#else /* #if defined(MEAT_CFG_LEAK) */
        free(
            p_buf);
#endif /* #if defined(MEAT_CFG_LEAK) */
    }
    else
    {
#if defined(MEAT_CFG_DBG)
        meat_dbg_break(
            p_ctxt,
            p_ctxt->p_dbg);
#endif /* #if defined(MEAT_CFG_DBG) */
    }

} /* meat_heap_free() */

/*

Function: meat_heap_init

Description:

    Initialize the meat_heap module.

*/
void
meat_heap_init(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_heap * const
        p_heap)
{
    (void)(
        p_ctxt);

    p_heap->b_init =
        1;

} /* meat_heap_init() */

/*

Function: meat_heap_cleanup

Description:

    Undo initialization of meat_heap module.

*/
void
meat_heap_cleanup(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_heap * const
        p_heap)
{
    (void)(
        p_ctxt);

    if (
        p_heap->b_init)
    {
#if defined(MEAT_CFG_LEAK)
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

                meat_trace_report(
                    p_ctxt,
                    p_ctxt->p_trace,
                    p_prefix->a_stack,
                    (unsigned int)(
                        sizeof(
                            p_prefix->a_stack)
                        / sizeof(
                            p_prefix->a_stack[0u])));

                p_iterator =
                    p_iterator->p_next;
            }

#if defined(MEAT_CFG_DBG)
            meat_dbg_break(
                p_ctxt,
                p_ctxt->p_dbg);
#endif /* #if defined(MEAT_CFG_DBG) */
        }
#endif /* #if defined(MEAT_CFG_LEAK) */

        p_heap->b_init =
            0;
    }

} /* meat_heap_cleanup() */

/* end-of-file: meat_heap.c */
