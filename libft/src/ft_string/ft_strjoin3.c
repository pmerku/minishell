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
#include <ft_memory.h>

char	*ft_strjoin3(char *a, char *b, char *c)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*str;

	if (!a || !b || !c)
		return (NULL);
	len1 = ft_strlen(a);
	len2 = ft_strlen(b);
	len3 = ft_strlen(c);
	str = ft_checked_malloc(sizeof(char) * (len1 + len2 + len3 + 1));
	ft_memcpy(str, a, len1 + 1);
	ft_memcpy(str + len1, b, len2 + 1);
	ft_memcpy(str + len1 + len2, c, len3 + 1);
	return (str);
}
