/* See LICENSE for license details. */

/*

Module: meat_main.h

Description:

    OS-independant main entry point of meat application.

*/

/* Header file dependencies */
#if !defined(INC_MEAT_OS_H)
#error include meat_os.h first
#endif /* #if !defined(INC_MEAT_OS_H) */

/* Reverse include guard */
#if defined(INC_MEAT_MAIN_H)
#error include meat_main.h once
#endif /* #if defined(INC_MEAT_MAIN_H) */

#define INC_MEAT_MAIN_H

/* Public functions of meat_main module ... */

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
int
    meat_main(
        unsigned int const
            argc,
        char const * const * const
            argv);

/* end-of-file: meat_main.h */
