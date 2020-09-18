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
