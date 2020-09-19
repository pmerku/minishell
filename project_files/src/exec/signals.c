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
#include <ft_exec.h>
#include <sys/wait.h>
#include <ft_errno.h>

void	f_signal_handler_exec(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("\n");
		if (signal(SIGINT, f_signal_handler_exec) == SIG_ERR)
		{
			set_errno(SIGNAL_ERROR);
			ft_printf("&cSignal handler error: &f%s&r\n",
				ft_strerror(get_errno()));
			exit(EXIT_FAILURE);
		}
	}
	else if (signo == SIGQUIT)
	{
		ft_printf("Quit\n");
		if (signal(SIGQUIT, f_signal_handler_exec) == SIG_ERR)
		{
			set_errno(SIGNAL_ERROR);
			ft_printf("&cSignal handler error: &f%s&r\n",
				ft_strerror(get_errno()));
			exit(EXIT_FAILURE);
		}
	}
}

void	f_signal_init_exec(void)
{
	if (signal(SIGINT, f_signal_handler_exec) == SIG_ERR)
	{
		set_errno(SIGNAL_ERROR);
		ft_printf("&cSignal handler error: &f%s&r\n",
			ft_strerror(get_errno()));
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, f_signal_handler_exec) == SIG_ERR)
	{
		set_errno(SIGNAL_ERROR);
		ft_printf("&cSignal handler error: &f%s&r\n",
			ft_strerror(get_errno()));
		exit(EXIT_FAILURE);
	}
}
