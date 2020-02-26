/* ************************************************************************** */
/*                                                                            */
/*   Project: minishell                                   ::::::::            */
/*   Members: dvoort, prmerku                           :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** A small library for managing memory for debugging purposes.
**
** When using this library, all `malloc` and `free` calls should be piped to
** this library, and not `stddef`, so that calls are tracked.
*/

#ifndef MEMMGMT_H
# define MEMMGMT_H

# include <stddef.h>

void			*ft_malloc(size_t n);
void			*ft_calloc(size_t n);
void			*ft_checked_malloc(size_t n);
void			*ft_checked_calloc(size_t n);
void			*ft_free(void *ptr);
void			*ft_nullcheck(void *data);
void			ft_exit(int code);
void			ft_err_exit(int code, char *msg);

#endif
