/* See LICENSE for license details. */

/*

Module: meat_os.c

Description:

*/

#include "meat_os.h"

#include "meat_main.h"

int
    main(
        int
            argc,
        char * *
            argv)
{
    return
        meat_main(
            (unsigned int)(
                argc),
            (char const * const *)(
                argv));

} /* main() */

/* end-of-file: meat_os.c */
