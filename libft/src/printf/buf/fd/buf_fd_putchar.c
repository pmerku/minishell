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

void	buf_fd_putchar(void *raw, char c)
{
	t_buf_fd *buf;

	buf = raw;
	buf->buf[buf->offset] = c;
	buf->offset++;
	buf->total_written++;
	if (buf->offset >= buf->buf_size)
		buf_fd_flush(buf);
}
