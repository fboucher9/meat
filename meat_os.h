/*

Module: meat_os.h

Description:

*/

#if defined(INC_MEAT_OS_H)
#error include meat_os.h once
#endif /* #if defined(INC_MEAT_OS_H) */

#define INC_MEAT_OS_H

/* For printf, ... */
#include <stdio.h>

/* For malloc and free, ... */
#include <stdlib.h>

/* For strcmp */
#include <string.h>

/* For mktime, localtime, ctime, ... */
#include <time.h>

/* For raise() */
#include <signal.h>

/* For backtrace() */
#include <execinfo.h>

/* end-of-file: meat_os.h */
