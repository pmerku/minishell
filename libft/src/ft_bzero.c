/* ************************************************************************** */
/*                                                                            */
/*   Project: project_files                                   ::::::::            */
/*   Members: dvoort, prmerku                           :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void			*ft_bzero(void *base, size_t n)
{
	size_t	i;
	char	*cast;

	i = 0;
	cast = (char *)base;
	while (i < n)
	{
		*(cast + i) = 0;
		i++;
	}
	return (cast);
}
