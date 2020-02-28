/* ************************************************************************** */
/*                                                                            */
/*   Project: project_files                                   ::::::::            */
/*   Members: dvoort, prmerku                           :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

void	buf_fd_putstr(void *raw, char *s)
{
	t_buf_fd *buf;

	buf = raw;
	while (*s != '\0')
	{
		buf->buf[buf->offset] = *s;
		buf->offset++;
		buf->total_written++;
		if (buf->offset >= buf->buf_size)
			buf_fd_flush(buf);
		s++;
	}
}
