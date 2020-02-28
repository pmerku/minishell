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

void	spec_charsprinted(t_ft_printf *pf, t_ft_fmt *fmt)
{
	signed int *ptr;

	(void)fmt;
	ptr = va_arg(*pf->args, signed int*);
	*ptr = buf_chars_printed(pf->buf);
}
