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

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*d_end;
	char	*s;
	char	*s_end;

	d = (char*)dst;
	s = (char*)src;
	if (!d && !s)
		return (NULL);
	if (d < s)
		ft_memcpy(dst, src, len);
	else
	{
		d_end = d + (len - 1);
		s_end = s + (len - 1);
		while (len)
		{
			*d_end = *s_end;
			d_end--;
			s_end--;
			len--;
		}
	}
	return (dst);
}
