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

int	buf_fd_chars_printed(void *buf)
{
	return (((t_buf_fd *)buf)->printed);
}
