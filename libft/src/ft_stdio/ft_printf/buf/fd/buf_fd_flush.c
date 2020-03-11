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

#include <unistd.h>
#include <ft_stdio/ft_printf_utils.h>
#include <stdlib.h>

void	buf_fd_flush(void *raw)
{
	t_buf_fd *buf;

	buf = raw;
	ssize_t result = write(buf->fd, buf->buf, buf->offset);
	if (result == -1)
	{
		exit(1);
	}
	buf->printed += buf->offset;
	buf->offset = 0;
}
