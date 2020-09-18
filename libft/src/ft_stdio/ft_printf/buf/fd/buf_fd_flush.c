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

#include <unistd.h>
#include <ft_stdio/ft_printf_utils.h>
#include <stdlib.h>

void	buf_fd_flush(void *raw)
{
	t_buf_fd	*buf;
	ssize_t		result;

	buf = raw;
	result = write(buf->fd, buf->buf, buf->offset);
	if (result == -1)
	{
		exit(1);
	}
	buf->printed += buf->offset;
	buf->offset = 0;
}
