/* See LICENSE for license details. */

/*

Module: meat_file.h

Description:

    Abstraction of file access.

*/

/* Header file dependency */
#if !defined(INC_MEAT_OS_H)
#error include meat_os.h first
#endif /* #if !defined(INC_MEAT_OS_H) */

#if defined(INC_MEAT_FILE_H)
#error include meat_file.h once
#endif /* #if defined(INC_MEAT_FILE_H) */

#define INC_MEAT_FILE_H

/* Predefine context handle */
struct meat_ctxt;

/* Predefine file handle */
struct meat_file;

/*

Enumeration: meat_file_type

Description:

*/
enum meat_file_type
{
    meat_file_type_stdin = 1,

    meat_file_type_stdout,

    meat_file_type_readonly,

    meat_file_type_writeonly,

    meat_file_type_append

}; /* enum meat_file_type */

struct meat_file;

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
struct meat_file *
meat_file_create(
    struct meat_ctxt * const
        p_ctxt,
    enum meat_file_type const
        e_type,
    char const * const
        p_name);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_file_destroy(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_file * const
        p_file);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
int
meat_file_read_char(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_file * const
        p_file);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_file_write_char(
    struct meat_ctxt * const
        p_ctxt,
    struct meat_file * const
        p_file,
    int const
        c_data);

/* end-of-file: meat_file.h */
