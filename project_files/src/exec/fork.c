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
#include <ft_parser.h>
#include <ft_env.h>
#include <sys/types.h>
#include <zconf.h>
#include <string.h>
#include <stdlib.h>
#include <ft_exec.h>
#include <ft_string.h>
#include <errno.h>
#include <ft_errno.h>
#include <utils.h>

static int	handle_fd_out(char **args, t_executor *exec, t_parser_command *list)
{
	if (exec->fd_out >= 0)
	{
		if (ft_dup2(exec->fd_out, STANDARD_OUT) == -1)
			exit(error_exit_helper(args, exec));
		ft_close(exec->fd_out);
		if (list != NULL)
		{
			ft_close(exec->pipe_next[PIPE_IN]);
			ft_close(exec->pipe_next[PIPE_OUT]);
		}
		if (get_errno() == CLOSE_ERROR)
			exit(error_exit_helper(args, exec));
	}
	else if (list != NULL)
	{
		if (ft_dup2(exec->pipe_next[PIPE_OUT], STANDARD_OUT) == -1)
			exit(error_exit_helper(args, exec));
		ft_close(exec->pipe_next[PIPE_IN]);
		ft_close(exec->pipe_next[PIPE_OUT]);
		if (get_errno() == CLOSE_ERROR)
			exit(error_exit_helper(args, exec));
	}
	return (EXIT_SUCCESS);
}

static int	handle_fd_in(char **args, t_executor *exec)
{
	if (exec->fd_in >= 0)
	{
		if (ft_dup2(exec->fd_in, STANDARD_IN) == -1)
			exit(error_exit_helper(args, exec));
		ft_close(exec->fd_in);
		if (exec->i != 0)
		{
			ft_close(exec->pipe_prev[PIPE_IN]);
			ft_close(exec->pipe_prev[PIPE_OUT]);
		}
		if (get_errno() == CLOSE_ERROR)
			exit(error_exit_helper(args, exec));
	}
	else if (exec->i != 0)
	{
		if (ft_dup2(exec->pipe_prev[PIPE_IN], STANDARD_IN) == -1)
			exit(error_exit_helper(args, exec));
		ft_close(exec->pipe_prev[PIPE_IN]);
		ft_close(exec->pipe_prev[PIPE_OUT]);
		if (get_errno() == CLOSE_ERROR)
			exit(error_exit_helper(args, exec));
	}
	return (EXIT_SUCCESS);
}

int			exec_fork(char **args, t_executor *exec, t_env *env,
			t_parser_command *list)
{
	f_signal_init_exec();
	exec->pid = fork();
	if (exec->pid == 0)
	{
		handle_fd_out(args, exec, list);
		handle_fd_in(args, exec);
		f_builtin_search(args, env);
		exec->path = env_resolve_path_file(env, args[0]);
		if (exec->path == NULL)
		{
			ft_printf("&cCommand not found: &f%s\n", args[0]);
			exit(COMMAND_NOT_FOUND);
		}
		execve(exec->path, args, env->vars);
		ft_printf("&cExecve error: &r%s\n", strerror(errno));
		exit(EXECVE_ERROR);
	}
	else if (exec->pid < 0)
	{
		ft_printf("&cFork error\n&r");
		return (exit_helper(args, exec));
	}
	return (EXIT_SUCCESS);
}
