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

#include <ft_stdio/ft_printf_utils.h>

struct s_col_combo	combinations[] = {
	{ '0', "30" },
	{ '1', "34" },
	{ '2', "32" },
	{ '3', "94" },
	{ '4', "31" },
	{ '5', "35" },
	{ '6', "33" },
	{ '7', "37" },
	{ '8', "90" },
	{ '9', "36" },
	{ 'a', "92" },
	{ 'b', "96" },
	{ 'c', "91" },
	{ 'd', "95" },
	{ 'e', "93" },
	{ 'f', "97" },
	{ 'r', "0" },
	{ 'l', "1" },
	{ 'm', "2" },
	{ 'n', "4" },
	{ 'o', "5" },
	{ 'i', "7" },
	{ 'h', "8" },
	{ '\0', ""}
};

static void			handle_spec(char **s, t_ft_printf *pf, t_ft_fmt *fmt)
{
	(*s)++;
	fmt_read(s, pf->args, fmt);
	fmt->orig_precision = fmt->precision;
	if (fmt->precision < 0)
		fmt->precision = 0;
	spec_get(fmt->specifier)(pf, fmt);
}

static void			handle_color(char **s, t_ft_printf *printf)
{
	char	col;
	char	*code;
	int		i;

	col = **s;
	(*s)++;
	if (col == '&')
	{
		buf_putchar(printf->buf, '&');
		return ;
	}
	i = 0;
	code = NULL;
	while (combinations[i].key != '\0')
	{
		if (combinations[i].key == col)
			code = combinations[i].code;
		i++;
	}
	if (code != NULL)
	{
		buf_putstr(printf->buf, "\033[");
		buf_putstr(printf->buf, code);
		buf_putchar(printf->buf, 'm');
	}
}

static void			ft_do_printf(char **s, t_ft_printf *printf)
{
	t_ft_fmt	fmt;

	while (**s != '\0')
	{
		if (**s == '&')
		{
			(*s)++;
			handle_color(s, printf);
		}
		else if (**s == '%')
		{
			handle_spec(s, printf, &fmt);
		}
		else
		{
			buf_putchar(printf->buf, **s);
			(*s)++;
		}
	}
}

int					ft_inner_printf(t_ft_printf *printf, const char *fmt)
{
	ft_do_printf((char **)&fmt, printf);
	buf_flush(printf->buf);
	return (buf_chars_printed(printf->buf));
}
