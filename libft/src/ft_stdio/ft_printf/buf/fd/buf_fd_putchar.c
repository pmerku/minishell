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
