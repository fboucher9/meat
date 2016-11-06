/* See LICENSE for license details. */

/*

Module: meat_list.h

Description:

*/

#if !defined(INC_MEAT_OS_H)
#error include meat_os.h first
#endif /* #if !defined(INC_MEAT_OS_H) */

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
meat_list_init(
    struct meat_list * const
        p_node);

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
