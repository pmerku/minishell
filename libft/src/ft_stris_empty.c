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

int		ft_stris_empty(const char *str)
{
	if (str == NULL)
		return (1);
	while (*str != '\0')
	{
		if (ft_isspace(*str))
			str++;
		else
			return (0);
	}
	return (1);
}
