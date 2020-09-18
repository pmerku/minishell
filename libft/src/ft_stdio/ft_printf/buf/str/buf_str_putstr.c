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

void	buf_str_putstr(void *raw, char *s)
{
	t_buf_str *buf;

	buf = raw;
	while (*s != '\0')
	{
		if (buf->offset < buf->buf_size)
		{
			buf->out[buf->offset] = *s;
			buf->offset++;
		}
		s++;
	}
}
