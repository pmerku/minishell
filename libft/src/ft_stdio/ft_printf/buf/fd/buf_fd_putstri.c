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

#include <ft_stdio/ft_printf_utils.h>

void	buf_fd_putstri(void *raw, char *s, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n && *s != '\0')
	{
		buf_fd_putchar(raw, *s);
		s++;
		i++;
	}
}
