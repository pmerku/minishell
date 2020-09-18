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
#include <ft_string.h>
#include <ft_stdlib.h>

static unsigned long long	spec_unsigned_int_read_val(t_ft_printf *pf,
		t_ft_fmt *fmt)
{
	va_list *args;

	args = pf->args;
	if (fmt->length == hh)
		return ((unsigned char)va_arg(*args, unsigned int));
	else if (fmt->length == h)
		return ((unsigned short)va_arg(*args, unsigned int));
	else if (fmt->length == l)
		return (va_arg(*args, unsigned long));
	else if (fmt->length == ll)
		return (va_arg(*args, unsigned long long));
	else
		return (va_arg(*args, unsigned int));
}

static char					read_into_buf(t_ft_printf *pf, t_ft_fmt *fmt,
		char *buf)
{
	unsigned long long	i;
	char				sign;

	sign = '\0';
	ft_memset(buf, '\0', 24);
	i = spec_unsigned_int_read_val(pf, fmt);
	ft_ulltoa(buf, i);
	if (fmt->force_nbr_sign == 1 && sign == '\0')
		sign = '+';
	if (fmt->whitespace_sign == 1 && sign == '\0')
		sign = ' ';
	if (fmt->precision_set == 1 && fmt->precision <= 0 && i == 0)
		buf[0] = '\0';
	return (sign);
}

static void					append_nbr_prefix(t_ft_printf *pf, t_ft_fmt *fmt,
		int nbr_space, char sign)
{
	char sign_size;

	if (sign == '\0')
		sign_size = 0;
	else
		sign_size = 1;
	if (fmt->leftpad_zeroes == 1 && fmt->precision_set == 0)
	{
		if (sign != '\0')
			buf_putchar(pf->buf, sign);
		if (fmt->left_justify == 0 && nbr_space > sign_size)
			buf_putchars(pf->buf, '0', nbr_space - sign_size);
	}
	else
	{
		if (fmt->left_justify == 0 && nbr_space > sign_size)
			buf_putchars(pf->buf, ' ', nbr_space - sign_size);
		if (sign != '\0')
			buf_putchar(pf->buf, sign);
	}
}

void						spec_unsigned_int(t_ft_printf *pf, t_ft_fmt *fmt)
{
	char		buf[24];
	char		sign;
	int			nbr_space;
	char		sign_size;

	sign = read_into_buf(pf, fmt, buf);
	if (fmt->precision_set == 0)
		fmt->precision = fmt->width;
	if (fmt->precision_set == 0)
		nbr_space = fmt->width - ft_strlen(buf);
	else
		nbr_space = fmt->width - ft_max(ft_abs(fmt->precision), ft_strlen(buf));
	if (sign == '\0')
		sign_size = 0;
	else
		sign_size = 1;
	append_nbr_prefix(pf, fmt, nbr_space, sign);
	if (fmt->precision_set == 1 && (int)ft_strlen(buf) < fmt->precision)
		buf_putchars(pf->buf, '0', fmt->precision - ft_strlen(buf));
	buf_putstr(pf->buf, buf);
	if (fmt->left_justify == 1 && nbr_space - sign_size > 0)
		buf_putchars(pf->buf, ' ', nbr_space - sign_size);
}
