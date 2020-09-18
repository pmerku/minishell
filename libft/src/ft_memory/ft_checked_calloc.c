/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/26 00:00:00 by anonymous     #+#    #+#                 */
/*   Updated: 2020/08/26 00:00:00 by anonymous     ########   odam.nl         */
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
