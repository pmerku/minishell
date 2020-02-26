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

int	ft_atoi(const char *str)
{
	long long		value;
	int				mul;
	unsigned int	i;

	i = 0;
	mul = 1;
	value = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		mul = (str[i] == '+' ? 1 : -1);
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		value *= 10;
		value += str[i] - '0';
		if (value < 0)
			return (mul == 1 ? -1 : 0);
		i++;
	}
	return ((int)(value * mul));
}
