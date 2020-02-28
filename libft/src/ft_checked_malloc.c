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

#include <memmgmt.h>

void		*ft_checked_malloc(size_t n)
{
	void *data;

	data = ft_malloc(n);
	if (data == NULL)
		ft_err_exit(1, "Error\nFailed checked malloc call\n");
	return (data);
}
