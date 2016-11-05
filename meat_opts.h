/* See LICENSE for license details. */

/*

Module: meat_opts.h

Description:

    Command-line options.

*/

/* Predefine */
struct meat_opts;

/*

Structure: meat_opts

Description:

*/
struct meat_opts
{
    time_t
        i_begin;

    time_t
        i_end;

}; /* struct meat_opts */

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
    meat_opts_init(
        struct meat_opts * const
            p_opts,
        unsigned int const
            i_argc,
        char const * const * const
            p_argv);

#if defined(__cplusplus)
extern "C"
#endif /* #if defined(__cplusplus) */
void
    meat_opts_cleanup(
        struct meat_opts * const
            p_opts);

/* end-of-file: meat_opts.h */
