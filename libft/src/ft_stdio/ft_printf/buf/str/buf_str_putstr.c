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

void	buf_str_putstr(void *raw, char *s)
{
	t_buf_str *buf;

	buf = raw;
	while (*s != '\0')
	{
		if (buf->offset < buf->buf_size)
		{
			buf->out[buf->offset] = *s;
			buf->offset++;
		}
		s++;
	}
}
