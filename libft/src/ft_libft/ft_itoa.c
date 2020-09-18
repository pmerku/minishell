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

#include <stddef.h>
#include <ft_libft.h>
#include <ft_memory.h>

char		*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	len = ft_intlen(n);
	str = ft_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	else if (n == 0)
		str[0] = '0';
	else
		n *= -1;
	str[len] = '\0';
	while (len && n)
	{
		str[len - 1] = -(n % 10) + 48;
		n /= 10;
		len--;
	}
	return (str);
}
