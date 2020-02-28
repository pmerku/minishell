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

void	buf_str_putstri(void *raw, char *s, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n && *s != '\0')
	{
		buf_str_putchar(raw, *s);
		s++;
		i++;
	}
}
