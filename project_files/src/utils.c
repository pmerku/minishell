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

#include <ft_llist.h>
#include <ft_libft.h>
#include <ft_stdio/ft_printf.h>
#include <ft_memory.h>
#include <ft_env.h>
#include <unistd.h>
#include <stdlib.h>
#include <ft_parser.h>
#include <signal.h>
#include <ft_errno.h>
#include <minishell.h>

void	cleanup(t_shell *shell)
{
	free_parse_results(shell->parse_tokens);
	ft_llist_free(&shell->lex_tokens);
	ft_free(shell->line);
	free(shell->dir);
}

void	signal_handler(int signo)
{
	char	*working_dir;

	if (signo == SIGINT)
	{
		ft_printf("\n");
		working_dir = getcwd(NULL, 0);
		ft_printf("\033[46;37m&f \xF0\x9F\x93\x81 %d %s&r ", 1, working_dir);
		free(working_dir);
		if (signal(SIGINT, signal_handler) == SIG_ERR)
		{
			set_errno(SIGNAL_ERROR);
			ft_printf("&cSignal handler error: &f%s&r\n",
				ft_strerror(get_errno()));
			exit(EXIT_FAILURE);
		}
	}
}

void	signal_init(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		set_errno(SIGNAL_ERROR);
		ft_printf("&cSignal handler error: &f%s&r\n",
			ft_strerror(get_errno()));
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		set_errno(SIGNAL_ERROR);
		ft_printf("&cSignal handler error: &f%s&r\n",
			ft_strerror(get_errno()));
		exit(EXIT_FAILURE);
	}
}
