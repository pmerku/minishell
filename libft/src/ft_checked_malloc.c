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

void		*ft_checked_malloc(size_t n)
{
	void *data;

	data = ft_malloc(n);
	if (data == NULL)
	{
		ft_eprintf(1, "Checked malloc failed\n");
	}
	return (data);
}
