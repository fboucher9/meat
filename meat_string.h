/* See LICENSE for license details. */

/*

Module: meat_string.h

Description:

    String utility functions.

*/

#if defined(INC_MEAT_STRING_H)
#error include meat_string.h once
#endif /* #if defined(INC_MEAT_STRING_H) */

#define INC_MEAT_STRING_H

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
char
    meat_string_is_whitespace(
        unsigned char const
            c_buf);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
size_t
    meat_string_skip_whitespace(
        unsigned char const * const
            p_buf,
        size_t const
            i_buf_len);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
size_t
    meat_string_trim_whitespace(
        unsigned char const * const
            p_buf,
        size_t const
            i_buf_len);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
size_t
    meat_string_find_whitespace(
        unsigned char const * const
            p_buf,
        size_t const
            i_buf_len);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
size_t
    meat_string_find_null(
        unsigned char const * const
            p_buf,
        size_t const
            i_buf_len);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
char
    meat_string_is_digit(
        unsigned char const
            c_buf);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed long int
    meat_string_scan_decimal(
        unsigned char const * const
            p_buf,
        size_t const
            i_buf_len);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
signed int
    meat_string_compare(
        unsigned char const * const
            p_buf_left,
        size_t const
            i_buf_left_len,
        unsigned char const * const
            p_buf_right,
        size_t const
            i_buf_right_len);

/* end-of-file: meat_string.h */
