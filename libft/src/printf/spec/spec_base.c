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
#include <libft.h>

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

static unsigned long long	read_into_buf(t_ft_printf *pf, t_ft_fmt *fmt,
		char *buf)
{
	unsigned long long	i;
	char				*base;

	base = "0123456789abcdef";
	if (fmt->specifier == 'o')
		base = "01234567";
	else if (fmt->specifier == 'X')
		base = "0123456789ABCDEF";
	ft_memset(buf, 130, '\0');
	i = spec_unsigned_int_read_val(pf, fmt);
	ft_ulltoa_base(buf, base, i);
	if (fmt->precision_set == 1 && fmt->precision <= 0 && i == 0)
		buf[0] = '\0';
	return (i);
}

static void					append_nbr_prefix(t_ft_printf *pf, t_ft_fmt *fmt,
		int nbr_space, unsigned long long i)
{
	if (fmt->leftpad_zeroes == 1 && fmt->precision_set == 0)
	{
		if (fmt->left_justify == 0 && nbr_space > 0 && fmt->hashtag == 0)
			buf_putchars(pf->buf, '0', nbr_space);
	}
	else
	{
		if (fmt->left_justify == 0 && nbr_space > 0)
			buf_putchars(pf->buf, ' ', nbr_space);
	}
	if (fmt->hashtag && i != 0)
		buf_putstr(pf->buf, "0x");
	if (fmt->leftpad_zeroes == 1 && fmt->precision_set == 0
			&& fmt->left_justify == 0 && nbr_space > 0 && fmt->hashtag == 1)
		buf_putchars(pf->buf, '0', nbr_space);
}

void						spec_base(t_ft_printf *pf, t_ft_fmt *fmt)
{
	unsigned long long		i;
	char					buf[130];
	int						nbr_space;

	i = read_into_buf(pf, fmt, buf);
	if (fmt->precision_set == 0)
		fmt->precision = fmt->width;
	if (fmt->precision_set == 0)
		nbr_space = fmt->width - ft_strlen(buf);
	else
		nbr_space = fmt->width - ft_max(ft_abs(fmt->precision), ft_strlen(buf));
	if (fmt->hashtag && i != 0)
		nbr_space -= 2;
	append_nbr_prefix(pf, fmt, nbr_space, i);
	if (fmt->precision_set == 1 && (int)ft_strlen(buf) < fmt->precision)
		buf_putchars(pf->buf, '0', fmt->precision - ft_strlen(buf));
	buf_putstr(pf->buf, buf);
	if (fmt->left_justify == 1 && nbr_space > 0)
		buf_putchars(pf->buf, ' ', nbr_space);
}
