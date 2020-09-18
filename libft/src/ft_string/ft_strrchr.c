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
#include <ft_string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	pos;

	ptr = NULL;
	if (c == '\0')
		return (ft_strchr(s, '\0'));
	while (*s)
	{
		pos = *s;
		if (c == pos)
			ptr = (char*)s;
		s++;
	}
	return (ptr);
}
