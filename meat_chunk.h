/* See LICENSE for license details. */

/*

Module: meat_chunk.h

Description:

    String of characters stored as a linked list of chunks (or parts).

*/

/* Header file dependencies */
#if !defined(INC_MEAT_LIST_H)
#error include meat_list.h first
#endif /* #if !defined(INC_MEAT_LIST_H) */

/* Reverse include guard */
#if defined(INC_MEAT_CHUNK_H)
#error include meat_chunk.h once
#endif /* #if defined(INC_MEAT_CHUNK_H) */

#define INC_MEAT_CHUNK_H

/* Number of characters in a single chunk */
#define MEAT_CHUNK_BUFFER_LENGTH 32u

/*

Structure: meat_chunk

Description:

    Data representation of a single chunk.

*/
struct meat_chunk
{
    struct meat_list
        o_list;

    unsigned int
        i_len;

    unsigned char
        a_buf[
            MEAT_CHUNK_BUFFER_LENGTH];

}; /* struct meat_chunk */

struct meat_chunk_list
{
    struct meat_list
        o_list;

    unsigned int
        i_total_len;

}; /* struct meat_chunk_list */

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_chunk_list_init(
    struct meat_chunk_list * const
        p_chunk_list);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_chunk_list_cleanup(
    struct meat_chunk_list * const
        p_chunk_list);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_chunk_list_write(
    struct meat_chunk_list * const
        p_chunk_list,
    unsigned char const
        c_data);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_chunk_list_read(
    struct meat_chunk_list * const
        p_chunk_list,
    unsigned char * const
        p_buf,
    unsigned int const
        i_buf_len);

/* end-o-file: meat_chunk.h */
