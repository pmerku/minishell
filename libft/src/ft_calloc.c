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

#include <libft.h>
#include <memmgmt.h>

void	*ft_calloc(size_t n)
{
	void	*out;

	out = ft_malloc(n);
	if (out == NULL)
		return (NULL);
	ft_bzero(out, n);
	return (out);
}
