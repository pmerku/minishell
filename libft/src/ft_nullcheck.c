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

#include <printf.h>

void	*ft_nullcheck(void *data)
{
	if (data == NULL)
	{
		ft_eprintf(1,
				"Error\nData null-check failed (got null, data expected)\n");
	}
	return (data);
}
