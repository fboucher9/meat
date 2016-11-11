/* See LICENSE for license details. */

/*

Module: meat_list.c

Description:

    Generic linked list to be used for all lists in meat project.

Comments:

    See header file for more details.

*/

#include "meat_os.h"

#include "meat_list.h"

/*

Function: meat_list_init()

Description:

    Initialize an element so that it's a list with a single element, itself.

Parameters:

    p_node
        Pointer to element to initialize

Returns: None.

Comments: None.

*/
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

/*

Function: meat_list_join()

Description:

    Join two elements together.

Parameters:

    p_before
        Pointer to first element to join.  This element will end up before
        the p_after element.

    p_after
        Pointer to second element to join.  This element will end up after
        the p_before element.

Comments:

    If the elements are in different lists, the two lists will become one.

    If the elements are in the same list, then there will be two lists.

*/
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

/*

Function: meat_list_iterate()

Description:

    Iterate all elements of list.  Use the callback function on each element
    of the list.  The list must have a fake element, the callback function
    will not be called for the fake element.

Parameters:

    p_node
        Pointer to fake element of list

    p_callback
        Pointer to callback function

    p_context
        Pointer to context that is passed to callback function

Returns: None.

Comments:

    Do not use this function to modify the list.  Do not call meat_list_join()
    from the callback function and do not modify the members of the element.

*/
void
meat_list_iterate(
    struct meat_list * const
        p_node,
    void (* const p_callback)(
        void * const
            p_context,
        struct meat_list * const
            p_list),
    void * const
        p_context)
{
    struct meat_list *
        p_iterator;

    p_iterator =
        p_node->p_next;

    while (
        p_iterator
        != p_node)
    {
        struct meat_list *
            p_next;

        p_next =
            p_iterator->p_next;

        (*p_callback)(
            p_context,
            p_iterator);

        p_iterator =
            p_next;
    }

} /* meat_list_iterate() */

/* end-of-file: meat_list.c */
