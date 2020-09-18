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

char	*ft_strip_chars(char *str, char c)
{
	size_t src;
	size_t pos;

	src = 0;
	pos = 0;
	while (str[src] != '\0')
	{
		if (str[src] != c)
		{
			str[pos] = str[src];
			pos++;
		}
		src++;
	}
	str[pos] = '\0';
	return (str);
}
