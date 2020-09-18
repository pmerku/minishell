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

int		ft_intlen_base(int n, int base)
{
	int		len;

	if (base < 2 || base > 16)
		return (0);
	len = (n <= 0);
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}
