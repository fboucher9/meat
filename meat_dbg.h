/* See LICENSE for license details. */

/*

Module: meat_dbg.h

Description:

*/

/* Header file dependencies */
#if !defined(INC_MEAT_OS_H)
#error include meat_os.h first
#endif /* #if !defined(INC_MEAT_OS_H) */

/* Reverse include guard */
#if defined(INC_MEAT_DBG_H)
#error include meat_dbg.h once
#endif /* #if defined(INC_MEAT_DBG_H) */

#define INC_MEAT_DBG_H

/* Predefine */
struct meat_ctxt;

/*

Structure: meat_dbg

Description:

*/
struct meat_dbg
{
    void *
        p_dummy;

}; /* struct meat_dbg */

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_dbg_break(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_dbg * const
        p_dbg);

/* end-of-file: meat_dbg.h */
