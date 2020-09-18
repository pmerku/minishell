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

int		ft_memcmp(const	void *s1, const	void *s2, size_t n)
{
	unsigned char	*src1;
	unsigned char	*src2;

	if (n)
	{
		src1 = (unsigned char*)s1;
		src2 = (unsigned char*)s2;
		while (n)
		{
			if (*src1 != *src2)
				return (*src1 - *src2);
			src1++;
			src2++;
			n--;
		}
	}
	return (0);
}
