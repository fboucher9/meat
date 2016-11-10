/* See LICENSE for license details. */

/*

Module: meat_dbg.c

Description:

*/

#include "meat_os.h"

#include "meat_dbg.h"

/* For raise() */
#include <signal.h>

/*

Function: meat_dbg_break

Description:

    None.

Parameters:

    None.

Returns:

    None.

Comments:

    None.

*/
void
meat_dbg_break(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_dbg * const
        p_dbg)
{
    (void)(
        p_ctxt);
    (void)(
        p_dbg);

    raise(
        SIGINT);

} /* meat_dbg_break() */

void
meat_dbg_init(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_dbg * const
        p_dbg)
{
    (void)(
        p_ctxt);

    p_dbg->b_init =
        1;

} /* meat_dbg_init() */

void
meat_dbg_cleanup(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_dbg * const
        p_dbg)
{
    (void)(
        p_ctxt);

    p_dbg->b_init =
        0;

} /* meat_dbg_cleanup() */

/* end-of-file: meat_dbg.c */
