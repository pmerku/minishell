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

int			ft_pf_atoi(char **str)
{
	long long	n;
	int			mul;

	n = 0;
	mul = 1;
	if (**str == '+' || **str == '-')
	{
		mul = (**str == '-' ? -1 : 1);
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		if (n * 10 < n)
			return (mul == -1 ? 0 : -1);
		n *= 10;
		n += (**str - '0');
		(*str)++;
	}
	return ((int)(mul * n));
}
