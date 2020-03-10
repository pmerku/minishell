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

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (n)
	{
		d = (unsigned char*)dst;
		s = (const unsigned char*)src;
		while (n)
		{
			*d = *s;
			if (*d == (unsigned char)c)
				return (d + 1);
			d++;
			s++;
			n--;
		}
	}
	return (NULL);
}
