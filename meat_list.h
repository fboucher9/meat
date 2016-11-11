/* See LICENSE for license details. */

/*

Module: meat_list.h

Description:

    Generic linked list to be used for all lists in meat project.

Comments:

    The list is a circular doubly linked list.  A fake element is used
    to point to first and last elements.  The same structure is used for
    each element including the fake element.  However, the fake element
    does not have the same derived type as the other elements.

    The caller is reponsible of casting the element to the derived type.
    Before casting, it is important to make sure that the element is
    not the fake element.  If the list is not the first member of the
    derived type, then it may be useful to use the offsetof() macro to
    get a pointer to the start of the derived type.

    The circular feature ensures that each element is part of a list.
    Operations may be done on a single element or on groups of elements.
    The same method is used to insert elements or to remove elements.
    See the examples section for more details.

Examples:

    -   create an empty list

            meat_list_init(&o_list);

    -   insert a first list before a second

            meat_list_join(&o_first, &o_second);

    -   insert a first list after a second

            meat_list_join(&o_second, &o_first);

    -   remove a single element from a list

            meat_list_join(&o_element, &o_element);

    -   remove a group of elements from a list

            meat_list_join(&o_last, &o_first);

Notes:

    To insert all elements of a list into another, you first need to
    detach the elements from the fake or else the final list may end up
    with two fake elements.

        p_first = o_fake.p_next;
        meat_list_join(&o_fake, &o_fake);
        meat_list_join(p_first, &o_other);

*/

/* Header file dependencies */
#if !defined(INC_MEAT_OS_H)
#error include meat_os.h first
#endif /* #if !defined(INC_MEAT_OS_H) */

/* Reverse include guard */
#if defined(INC_MEAT_LIST_H)
#error include meat_list.h once
#endif /* #if defined(INC_MEAT_LIST_H) */

#define INC_MEAT_LIST_H

/*

Structure: meat_list

Description:

*/
struct meat_list
{
    struct meat_list *
        p_next;

    struct meat_list *
        p_prev;

}; /* struct meat_list */

/* Public functions ... */

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_list_init(
    struct meat_list * const
        p_node);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_list_join(
    struct meat_list * const
        p_before,
    struct meat_list * const
        p_after);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
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
        p_context);

/* end-of-file: meat_list.h */
