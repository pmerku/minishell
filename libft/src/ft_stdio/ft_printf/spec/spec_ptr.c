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
#include <ft_string.h>
#include <ft_stdlib.h>

static unsigned long long	spec_unsigned_int_read_val(t_ft_printf *pf)
{
	va_list *args;

	args = pf->args;
	return ((unsigned long long)va_arg(*args, void*));
}

static unsigned long long	read_into_buf(t_ft_printf *pf, char *buf,
		t_ft_fmt *fmt)
{
	unsigned long long	i;

	ft_memset(buf, 130, '\0');
	i = spec_unsigned_int_read_val(pf);
	ft_ulltoa_base(buf, "0123456789abcdef", i);
	if (fmt->precision_set == 1 && fmt->precision == 0 && i == 0)
		buf[0] = '\0';
	return (i);
}

static void					append_nbr_prefix(t_ft_printf *pf, t_ft_fmt *fmt,
		int nbr_space)
{
	if (!(fmt->leftpad_zeroes == 1 && fmt->precision_set == 0))
	{
		if (fmt->left_justify == 0 && nbr_space > 0)
			buf_putchars(pf->buf, ' ', nbr_space);
	}
	buf_putstr(pf->buf, "0x");
	if (fmt->leftpad_zeroes == 1 && fmt->precision_set == 0
			&& fmt->left_justify == 0 && nbr_space > 0)
		buf_putchars(pf->buf, '0', nbr_space);
}

void						spec_ptr(t_ft_printf *pf, t_ft_fmt *fmt)
{
	char					buf[130];
	int						nbr_space;

	read_into_buf(pf, buf, fmt);
	if (fmt->precision_set == 0)
		fmt->precision = fmt->width;
	if (fmt->precision_set == 0)
		nbr_space = fmt->width - ft_strlen(buf);
	else
		nbr_space = fmt->width - ft_max(ft_abs(fmt->precision), ft_strlen(buf));
	nbr_space -= 2;
	append_nbr_prefix(pf, fmt, nbr_space);
	if (fmt->precision_set == 1 && (int)ft_strlen(buf) < fmt->precision)
		buf_putchars(pf->buf, '0', fmt->precision - ft_strlen(buf));
	buf_putstr(pf->buf, buf);
	if (fmt->left_justify == 1 && nbr_space > 0)
		buf_putchars(pf->buf, ' ', nbr_space);
}
