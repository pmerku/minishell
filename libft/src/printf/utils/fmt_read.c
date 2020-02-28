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

static void			fmt_read_flags(t_ft_fmt *fmt, char **str)
{
	while (**str != '\0' && (**str == '-' || **str == '+'
			|| **str == ' ' || **str == '#' || **str == '0'))
	{
		if (**str == '-')
			fmt->left_justify = 1;
		else if (**str == '+')
			fmt->force_nbr_sign = 1;
		else if (**str == ' ')
			fmt->whitespace_sign = 1;
		else if (**str == '#')
			fmt->hashtag = 1;
		else if (**str == '0')
			fmt->leftpad_zeroes = 1;
		(*str)++;
	}
	if (fmt->left_justify)
		fmt->leftpad_zeroes = 0;
}

static void			fmt_read_width(t_ft_fmt *fmt, char **str, va_list *args)
{
	if (**str == '\0' || (**str != '*' && !(**str >= '0' && **str <= '9')))
		return ;
	if (**str == '*')
	{
		fmt->width = va_arg(*args, int);
		(*str)++;
	}
	else
		fmt->width = ft_pf_atoi(str);
	if (fmt->width < 0)
	{
		fmt->left_justify = 1;
		fmt->width = -fmt->width;
	}
}

static void			fmt_read_precision(t_ft_fmt *fmt, char **str, va_list *args)
{
	if (**str == '\0' || **str != '.')
		return ;
	fmt->precision_set = 1;
	(*str)++;
	if (**str == '-')
		fmt->left_justify = 1;
	if (**str == '*')
	{
		fmt->precision = va_arg(*args, int);
		(*str)++;
	}
	else
		fmt->precision = ft_pf_atoi(str);
}

static void			fmt_read_length(t_ft_fmt *fmt, char **str)
{
	if (**str == 'h' && *((*str) + 1) == 'h')
		fmt->length = hh;
	else if (**str == 'h')
		fmt->length = h;
	else if (**str == 'l' && *((*str) + 1) == 'l')
		fmt->length = ll;
	else if (**str == 'l')
		fmt->length = l;
	else if (**str == 'j')
		fmt->length = j;
	else if (**str == 'z')
		fmt->length = z;
	else if (**str == 't')
		fmt->length = t;
	else if (**str == 'L')
		fmt->length = l;
	else
		fmt->length = none;
	if (fmt->length != none)
		(*str)++;
	if (fmt->length == hh || fmt->length == ll)
		(*str)++;
}

void				fmt_read(char **str, va_list *args, t_ft_fmt *fmt)
{
	fmt->specifier = 0;
	fmt->left_justify = 0;
	fmt->force_nbr_sign = 0;
	fmt->whitespace_sign = 0;
	fmt->hashtag = 0;
	fmt->leftpad_zeroes = 0;
	fmt->precision_set = 0;
	fmt->precision = 0;
	fmt->orig_precision = 0;
	fmt->width = 0;
	fmt->length = none;
	fmt_read_flags(fmt, str);
	fmt_read_width(fmt, str, args);
	fmt_read_precision(fmt, str, args);
	fmt_read_length(fmt, str);
	fmt->specifier = **str;
	if (fmt->specifier != '\0')
		(*str)++;
}
