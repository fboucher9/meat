/* See LICENSE for license details. */

/*

Module: meat_string.c

Description:

    String utility functions.

*/

#include "meat_os.h"

#include "meat_string.h"

char
meat_string_is_whitespace(
    unsigned char const
        c_buf)
{
    return
        (char)(
            (
                (unsigned char)(' ')
                == c_buf)
            || (
                (unsigned char)('\r')
                == c_buf)
            || (
                (unsigned char)('\t')
                == c_buf)
            || (
                (unsigned char)('\n')
                == c_buf));

}

size_t
meat_string_skip_whitespace(
    unsigned char const * const
        p_buf,
    size_t const
        i_buf_len)
{
    size_t
        i_offset;

    i_offset =
        0u;

    while (
        (
            i_offset
            < i_buf_len)
        &&
            meat_string_is_whitespace(
                p_buf[i_offset]))
    {
        i_offset ++;
    }

    return
        i_offset;

}

size_t
    meat_string_trim_whitespace(
        unsigned char const * const
            p_buf,
        size_t const
            i_buf_len)
{
    size_t
        i_offset;

    i_offset =
        i_buf_len;

    while (
        (
            0
            != i_offset)
        && (
            meat_string_is_whitespace(
                p_buf[i_offset - 1u])))
    {
        i_offset --;
    }

    return
        i_offset;

}

size_t
    meat_string_find_whitespace(
        unsigned char const * const
            p_buf,
        size_t const
            i_buf_len)
{
    size_t
        i_offset;

    i_offset =
        0u;

    while (
        (
            i_offset
            < i_buf_len)
        &&
            !(
                meat_string_is_whitespace(
                    p_buf[i_offset])))
    {
        i_offset ++;
    }

    return
        i_offset;

}

size_t
    meat_string_find_null(
        unsigned char const * const
            p_buf,
        size_t const
            i_buf_len)
{
    size_t
        i_offset;

    i_offset =
        0u;

    while (
        (
            i_offset
            < i_buf_len)
        &&
            (
                '\000'
                != p_buf[i_offset]))
    {
        i_offset ++;
    }

    return
        i_offset;


} /* meat_string_find_null() */

char
    meat_string_is_digit(
        unsigned char const
            c_buf)
{
    return
        (char)(
            (
                (unsigned char)('0')
                <= c_buf)
            && (
                (unsigned char)('9')
                >= c_buf));

}

signed long int
    meat_string_scan_decimal(
        unsigned char const * const
            p_buf,
        size_t const
            i_buf_len)
{
    signed long int
        i_value;

    size_t
        i_offset;

    char
        b_negative;

    i_value =
        0l;

    i_offset =
        0;

    b_negative =
        0;

    if (
        (
            i_offset
            < i_buf_len)
        && (
            '-'
            == p_buf[i_offset]))
    {
        b_negative =
            1;

        i_offset ++;
    }

    if (
        (
            i_offset
            < i_buf_len)
        && (
            '+'
            == p_buf[i_offset]))
    {
        b_negative =
            0;

        i_offset ++;
    }

    while (
        i_offset
        < i_buf_len)
    {
        if (
            meat_string_is_digit(
                p_buf[i_offset]))
        {
            i_value =
                (signed long int)(
                    (
                        i_value
                        * 10l)
                    + (signed long int)(
                        p_buf[i_offset]
                        - '0'));
        }

        i_offset ++;
    }

    return
        i_value;

}

signed int
    meat_string_compare(
        unsigned char const * const
            p_buf_left,
        size_t const
            i_buf_left_len,
        unsigned char const * const
            p_buf_right,
        size_t const
            i_buf_right_len)
{
    int
        i_result;

    size_t
        i_buf_iterator;

    i_buf_iterator =
        0u;

    do
    {
        i_result =
            (int)(
                (int)(
                    (
                        i_buf_iterator
                        < i_buf_left_len)
                    ?  p_buf_left[i_buf_iterator]
                    : '\0')
                - (int)(
                    (
                        i_buf_iterator
                        < i_buf_right_len)
                    ? p_buf_right[i_buf_iterator]
                    : '\0')
                );

        i_buf_iterator ++;
    }
    while (
        (
            (
                i_buf_iterator
                < i_buf_left_len)
            || (
                i_buf_iterator
                < i_buf_right_len))
        && (
            0
            == i_result));

    return
        i_result;

} /* meat_string_compare() */

/* end-of-file: meat_string.c */
