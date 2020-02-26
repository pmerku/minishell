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

#include <unistd.h>
#include <printf_utils.h>

void	buf_fd_flush(void *raw)
{
	t_buf_fd *buf;

	buf = raw;
	write(buf->fd, buf->buf, buf->offset);
	buf->printed += buf->offset;
	buf->offset = 0;
}
