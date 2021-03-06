/* See LICENSE for license details. */

/*

Module: meat_dbg.h

Description:

*/

/* Header file dependencies */
#if !defined(INC_MEAT_OS_H)
#error include meat_os.h first
#endif /* #if !defined(INC_MEAT_OS_H) */

#if !defined(INC_MEAT_CFG_H)
#error include meat_cfg.h before
#endif /* #if !defined(INC_MEAT_CFG_H) */

/* Validate configuration */
#if !defined(MEAT_CFG_DBG)
#error feature is disabled
#endif /* #if !defined(MEAT_CFG_DBG) */

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
    char
        b_init;

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

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_dbg_init(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_dbg * const
        p_dbg);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_dbg_cleanup(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_dbg * const
        p_dbg);

/* end-of-file: meat_dbg.h */
