/* See LICENSE for license details. */

/*

Module: meat_list.c

Description:

*/

#include "meat_os.h"

#include "meat_list.h"

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

void
meat_list_init(
    struct meat_list * const
        p_node)
{
    p_node->p_next =
        p_node;

    p_node->p_prev =
        p_node;

} /* meat_list_init() */

/* end-of-file: meat_list.c */
