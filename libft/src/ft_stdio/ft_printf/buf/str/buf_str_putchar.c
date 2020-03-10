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

void	buf_str_putchar(void *raw, char c)
{
	t_buf_str *buf;

	buf = raw;
	if (buf->offset < buf->buf_size)
	{
		buf->out[buf->offset] = c;
		buf->offset++;
	}
}
