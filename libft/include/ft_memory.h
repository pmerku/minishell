/* ************************************************************************** */
/*                                                                            */
/*   Project: custom_libc                                 ::::::::            */
/*   Members: dvoort, prmerku                           :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMORY_H
# define FT_MEMORY_H

# include <stddef.h>

void	ft_bzero(void *s, size_t n);
void	*ft_checked_malloc(size_t n);
void	*ft_malloc(size_t n);
void	*ft_checked_calloc(size_t count, size_t size);
void	*ft_calloc(size_t count, size_t size);
void	*ft_free(void *ptr);
char	**ft_free_array(char **arr);
void	*ft_nullcheck(void *data);

#endif
