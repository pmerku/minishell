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
