/* See LICENSE for license details. */

/*

Module: meat_cfg.h

Description:

    Compile-time configuration of features.

*/

/* Reverse include guard */
#if defined(INC_MEAT_CFG_H)
#error include meat_cfg.h once
#endif /* #if defined(INC_MEAT_CFG_H) */

#define INC_MEAT_CFG_H

/* Enable debug interface */
#define MEAT_CFG_DBG

/* Enable memory leak detection */
#define MEAT_CFG_LEAK

/* end-of-file: meat_cfg.h */
