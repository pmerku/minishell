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

int		ft_printf(const char *fmt, ...)
{
	va_list			args;
	t_ft_printf		printf;
	t_buf			buf;
	t_buf_fd		fd_inner;
	int				ret_val;

	buf_fd_create(&buf, &fd_inner, 1);
	buf_reset(&buf);
	printf.buf = &buf;
	va_start(args, fmt);
	printf.args = &args;
	ret_val = ft_inner_printf(&printf, fmt);
	va_end(args);
	return (ret_val);
}
