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

int		ft_snprintf(char *str, size_t size, const char *fmt, ...)
{
	va_list			args;
	t_ft_printf		printf;
	t_buf			buf;
	t_buf_str		buf_inner;
	int				ret_val;

	if (size == 0)
		return (0);
	buf_str_create(&buf, &buf_inner, str, size);
	buf_reset(&buf);
	printf.buf = &buf;
	va_start(args, fmt);
	printf.args = &args;
	ret_val = ft_inner_printf(&printf, fmt);
	va_end(args);
	str[buf_chars_printed(&buf)
		- ((size_t)buf_chars_printed(&buf) == size ? 1 : 0)] = '\0';
	return (ret_val);
}