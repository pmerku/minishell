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

#include <memmgmt.h>

void		*ft_checked_calloc(size_t n)
{
	void *data;

	data = ft_calloc(n);
	if (data == NULL)
		ft_err_exit(1, "Error\nFailed checked calloc call\n");
	return (data);
}
