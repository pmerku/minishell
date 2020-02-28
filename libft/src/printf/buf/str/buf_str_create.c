/* ************************************************************************** */
/*                                                                            */
/*   Project: minishell                                   ::::::::            */
/*   Members: dvoort, prmerku                           :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

void				buf_str_create(t_buf *buf, t_buf_str *str_buf, char *str,
		size_t buf_size)
{
	buf->metadata = str_buf;
	str_buf->buf_size = buf_size;
	str_buf->out = str;
	buf->reset = &buf_str_reset;
	buf->putstr = &buf_str_putstr;
	buf->putstri = &buf_str_putstri;
	buf->putchar = &buf_str_putchar;
	buf->putchars = &buf_str_putchars;
	buf->chars_printed = &buf_str_chars_printed;
	buf->flush = &buf_str_flush;
	buf->reset(buf->metadata);
}
