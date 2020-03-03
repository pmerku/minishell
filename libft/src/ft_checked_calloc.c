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
#include <printf.h>

void		*ft_checked_calloc(size_t n)
{
	void *data;

	data = ft_calloc(n);
	if (data == NULL)
		ft_eprintf(1, "Error\nFailed checked calloc call\n");
	return (data);
}
