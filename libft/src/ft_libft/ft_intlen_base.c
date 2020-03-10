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
