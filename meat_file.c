/* See LICENSE for license details. */

/*

Module: meat_file.c

Description:

    Abstraction of file access.

*/

#include "meat_os.h"

#include <stdio.h>

#include "meat_file.h"

#include "meat_ctxt.h"

#include "meat_heap.h"

/*

Structure: meat_file

Description:

*/
struct meat_file
{
    FILE *
        p_private;

}; /* struct meat_file */

struct meat_file *
    meat_file_create(
        struct meat_ctxt * const
            p_ctxt,
        enum meat_file_type const
            e_type,
        char const * const
            p_name)
{
    struct meat_file *
        p_file;

    p_file =
        (struct meat_file *)(
            meat_heap_alloc(
                p_ctxt,
                p_ctxt->p_heap,
                sizeof(
                    struct meat_file)));

    if (
        p_file)
    {
        if (
            meat_file_type_stdin
            == e_type)
        {
            p_file->p_private =
                stdin;
        }
        else if (
            meat_file_type_stdout
            == e_type)
        {
            p_file->p_private =
                stdout;
        }
        else if (
            meat_file_type_readonly
            == e_type)
        {
            p_file->p_private =
                fopen(
                    p_name,
                    "r");
        }
        else if (
            meat_file_type_writeonly
            == e_type)
        {
            p_file->p_private =
                fopen(
                    p_name,
                    "w");
        }
        else if (
            meat_file_type_append
            == e_type)
        {
            p_file->p_private =
                fopen(
                    p_name,
                    "a");
        }
        else
        {
            p_file->p_private =
                NULL;
        }

        if (
            p_file->p_private)
        {
        }
        else
        {
            meat_heap_free(
                p_ctxt,
                p_ctxt->p_heap,
                (void *)(
                    p_file));

            p_file =
                (struct meat_file *)(
                    0);
        }
    }

    return
        p_file;

} /* meat_file_create() */

void
    meat_file_destroy(
        struct meat_ctxt * const
            p_ctxt,
        struct meat_file * const
            p_file)
{
    if (
        p_file->p_private)
    {
        if (
            (
                p_file->p_private != stdin)
            && (
                p_file->p_private != stdout))
        {
            fclose(
                p_file->p_private);

        }

        p_file->p_private = NULL;
    }

    meat_heap_free(
        p_ctxt,
        p_ctxt->p_heap,
        (void *)(
            p_file));

} /* meat_file_destroy() */

int
    meat_file_read_char(
        struct meat_ctxt * const
            p_ctxt,
        struct meat_file * const
            p_file)
{
    int
        i_data;

    (void)(
        p_ctxt);

    if (
        p_file->p_private)
    {
        i_data =
            fgetc(
                p_file->p_private);
    }
    else
    {
        i_data =
            -1;
    }

    return
        i_data;

} /* meat_file_read_char() */

void
    meat_file_write_char(
        struct meat_ctxt * const
            p_ctxt,
        struct meat_file * const
            p_file,
        int const
            c_data)
{
    (void)(
        p_ctxt);

    if (
        p_file->p_private)
    {
        fputc(
            c_data,
            p_file->p_private);
    }
} /* meat_file_write_char() */

/* end-of-file: meat_file.c */
