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

#include <ft_memory.h>
#include <ft_stdio/ft_printf.h>

void		*ft_checked_calloc(size_t count, size_t size)
{
	void *data;

	data = ft_calloc(count, size);
	if (data == NULL)
		ft_eprintf(1, "Error\nFailed checked calloc call\n");
	return (data);
}

