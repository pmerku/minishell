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

#include <stddef.h>

void			*ft_memset(void *base, size_t n, char set)
{
	size_t	i;
	char	*cast;

	i = 0;
	cast = (char *)base;
	while (i < n)
	{
		*(cast + i) = set;
		i++;
	}
	return (cast);
}
