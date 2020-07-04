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

#include <ft_stdio/ft_printf.h>
#include <ft_env.h>
#include <sys/types.h>
#include <zconf.h>
#include <string.h>
#include <stdlib.h>
#include <ft_exec.h>
#include <ft_string.h>
#include <sys/wait.h>
#include <errno.h>

static void	_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("\n");
		signal(SIGINT, _signal_handler);
	}
	else if (signo == SIGQUIT)
	{
		ft_printf("Quit\n");
		signal(SIGQUIT, _signal_handler);
	}
}

int			exec_fork(t_executor *exec, char **args, t_env *env)
{
	exec->pid = fork();
	if (exec->pid < 0)
	{
		ft_printf("&cFork error\n&r");
		return (exit_helper(args, exec));
	}
	signal(SIGINT, _signal_handler);
	signal(SIGQUIT, _signal_handler);
	if (exec->pid == 0)
	{
//		close(exec->fd_pipe[PIPE_IN]);
//		dup2(exec->fd_in, STANDARD_IN);
		close(exec->fd_in);
		char *path = env_resolve_path_file(env, args[0]);
		if (path == NULL)
		{
			ft_printf("&cCommand not found: &f%s\n", args[0]);
			exit(COMMAND_NOT_FOUND);
		}
		execve(path, args, env->vars);
		ft_printf("&cExecve error: &r%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
