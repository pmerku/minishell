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

#include <ft_stdio/ft_printf.h>
#include <stdlib.h>
#include <ft_errno.h>
#include <utils.h>
#include <unistd.h>

void	ft_close(int fd)
{
	if (close(fd) == -1)
	{
		set_errno(CLOSE_ERROR);
		ft_printf("&cError closing file: &f%s&r\n", ft_strerror(get_errno()));
	}
}

int		ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		set_errno(DUP2_ERROR);
		ft_printf("&cError: &f%s\n&r", ft_strerror(get_errno()));
		return (-1);
	}
	return (EXIT_SUCCESS);
}

int		ft_pipe(int *pipe_dest)
{
	if (pipe(pipe_dest) == -1)
	{
		set_errno(PIPE_ERROR);
		ft_printf("&cPipe error: &f%s\n&r", ft_strerror(get_errno()));
		return (-1);
	}
	return (EXIT_SUCCESS);
}

int		ft_dup(int fd)
{
	int	tmp;

	tmp = dup(fd);
	if (tmp == -1)
	{
		set_errno(DUP_ERROR);
		ft_printf("&cError: &f%s\n&r", ft_strerror(get_errno()));
		return (-1);
	}
	return (tmp);
}
