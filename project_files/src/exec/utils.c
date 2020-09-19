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
