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

#include <ft_errno.h>
#include <ft_stdio/ft_printf.h>
#include <unistd.h>

void	ft_close(int fd)
{
	if (close(fd) != 0)
	{
		set_errno(CLOSE_ERROR);
		ft_printf("&cError closing file: &f%s&r\n", ft_strerror(get_errno()));
	}
}
