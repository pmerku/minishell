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

void		buf_fd_reset(void *raw)
{
	t_buf_fd *buf;

	buf = raw;
	buf->offset = 0;
	buf->printed = 0;
	buf->total_written = 0;
	buf->buf_size = 128;
}
