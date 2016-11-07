/* See LICENSE for license details. */

/*

Module: meat_file.c

Description:

    Abstraction of file access.

*/

#include "meat_os.h"

#include "meat_file.h"

char
    meat_file_init(
        struct meat_file * const
            p_file,
        enum meat_file_type const
            e_type,
        char const * const
            p_name)
{
    char
        b_result;

    if (
        meat_file_type_stdin
        == e_type)
    {
        p_file->p_private =
            stdin;

        b_result =
            1;
    }
    else if (
        meat_file_type_stdout
        == e_type)
    {
        p_file->p_private =
            stdout;

        b_result =
            1;
    }
    else if (
        meat_file_type_readonly
        == e_type)
    {
        p_file->p_private =
            fopen(
                p_name,
                "r");

        if (
            p_file->p_private)
        {
            b_result =
                1;
        }
        else
        {
            b_result =
                0;
        }
    }
    else if (
        meat_file_type_writeonly
        == e_type)
    {
        p_file->p_private =
            fopen(
                p_name,
                "w");

        if (
            p_file->p_private)
        {
            b_result =
                1;
        }
        else
        {
            b_result =
                0;
        }
    }
    else if (
        meat_file_type_append
        == e_type)
    {
        p_file->p_private =
            fopen(
                p_name,
                "a");

        if (
            p_file->p_private)
        {
            b_result =
                1;
        }
        else
        {
            b_result =
                0;
        }
    }
    else
    {
        b_result =
            0;
    }

    return
        b_result;

} /* meat_file_init() */

void
    meat_file_cleanup(
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

} /* meat_file_cleanup() */

int
    meat_file_read_char(
        struct meat_file * const
            p_file)
{
    int
        i_data;

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
        struct meat_file * const
            p_file,
        int const
            c_data)
{
    if (
        p_file->p_private)
    {
        fputc(
            c_data,
            p_file->p_private);
    }
} /* meat_file_write_char() */

/* end-of-file: meat_file.c */
