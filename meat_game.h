/* See LICENSE for license details. */

/*

Module: meat_game.h

Description:

    Database of games, events or television shows.

*/

/* Header file dependencies */
#if !defined(INC_MEAT_OS_H)
#error include meat_os.h first
#endif /* #if !defined(INC_MEAT_OS_H) */

/* Header file dependencies */
#if !defined(INC_MEAT_LIST_H)
#error include meat_list.h before
#endif /* #if !defined(INC_MEAT_LIST_H) */

#if defined(INC_MEAT_GAME_H)
#error include meat_game.h once
#endif /* #if defined(INC_MEAT_GAME_H) */

#define INC_MEAT_GAME_H

/* Predefine */
struct meat_game;

/* Predefine */
struct meat_file;

/*

Structure: meat_game

Description:

    Information about a single game, event or television show.

*/
struct meat_game
{
    struct meat_list
        o_list;

    signed long int
        i_game_time;

    char
        a_remarks[256u];

}; /* struct meat_game */

/*

Structure: meat_game_list

Description:

    List of meat_game structures.

*/
struct meat_game_list
{
    struct meat_list
        o_list;

}; /* struct meat_game_list */

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
char
meat_game_list_init(
    struct meat_game_list * const
        p_list,
    struct meat_file * const
        p_file);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_game_list_cleanup(
    struct meat_game_list * const
        p_meat_game_list);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
meat_game_list_iterate(
    struct meat_game_list * const
        p_meat_game_list,
    void (* p_callback)(
        void * const
            p_context,
        struct meat_game * const
            p_game),
    void * const
        p_context);

/* end-of-file: meat_game.h */
