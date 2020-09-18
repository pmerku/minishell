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

static void		ft_lltoa_inner(char *out, long long value, int *i)
{
	if (value > 9)
		ft_lltoa_inner(out, value / 10, i);
	out[*i] = '0' + (value % 10);
	(*i)++;
}

char			ft_lltoa(char *out, long long value)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	if (value == 0)
	{
		out[0] = '0';
		return ('\0');
	}
	if (value == -9223372036854775807LL - 1)
	{
		out[0] = '9';
		value = -223372036854775808;
		i++;
	}
	if (value < 0)
	{
		value *= -1;
		c = '-';
	}
	ft_lltoa_inner(out, value, &i);
	return (c);
}
