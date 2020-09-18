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

#include <ft_stdio/ft_printf_utils.h>

void				buf_fd_create(t_buf *buf, t_buf_fd *fd_buf, int fd)
{
	buf->metadata = fd_buf;
	fd_buf->fd = fd;
	buf->reset = &buf_fd_reset;
	buf->putstr = &buf_fd_putstr;
	buf->putstri = &buf_fd_putstri;
	buf->putchar = &buf_fd_putchar;
	buf->putchars = &buf_fd_putchars;
	buf->chars_printed = &buf_fd_chars_printed;
	buf->flush = &buf_fd_flush;
	buf->reset(buf->metadata);
}
