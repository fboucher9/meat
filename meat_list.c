/*

Module: meat_list.c

Description:

*/

#include "meat_os.h"

#include "meat_list.h"

#include "meat_heap.h"

void
meat_list_join(
    struct meat_list * const
        p_before,
    struct meat_list * const
        p_after)
{
    /* AB(C) - (D)EF > ABCDEF */
    p_before->p_next->p_prev =
        p_after->p_prev;

    p_after->p_prev->p_next =
        p_before->p_next;

    p_before->p_next =
        p_after;

    p_after->p_prev =
        p_before;

} /* meat_list_join() */

struct meat_list *
meat_list_alloc(
    void * p_data)
{
    struct meat_list *
        p_node;

    p_node =
        (struct meat_list *)(
            meat_heap_alloc(
                sizeof(
                    struct meat_list)));

    if (
        p_node)
    {
        p_node->p_next =
            p_node;

        p_node->p_prev =
            p_node;

        p_node->p_data =
            p_data;
    }

    return
        p_node;

} /* meat_list_alloc() */

void
meat_list_free(
    struct meat_list * const
        p_node)
{
    meat_list_join(
        p_node,
        p_node);

    meat_heap_free(
        p_node);

} /* meat_list_free() */

/* end-of-file: meat_list.c */
