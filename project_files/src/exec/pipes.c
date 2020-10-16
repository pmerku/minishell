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
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <ft_memory.h>
#include <builtins.h>
#include <ft_errno.h>
#include <utils.h>
#include <sys/stat.h>

void	init_pipes(t_executor *exec)
{
	ft_bzero(exec, sizeof(*exec));
	exec->pipe_prev[PIPE_IN] = -1;
	exec->pipe_prev[PIPE_OUT] = -1;
	exec->pipe_next[PIPE_IN] = -1;
	exec->pipe_next[PIPE_OUT] = -1;
	exec->i = 0;
}

int		make_pipes(t_executor *exec, t_parser_command **list,
		t_parser_command *command, t_env *env)
{
	if (list[1] != NULL && list[exec->i + 1] != NULL
		&& ft_pipe(exec->pipe_next) == -1)
	{
		error_exit_helper(exec->args, exec);
		return (EXIT_FAILURE);
	}
	exec->fd_in = get_in_fd(command, env);
	if (exec->fd_in == -2 || exec->fd_in == -3)
	{
		error_exit_helper(exec->args, exec);
		return (EXIT_FAILURE);
	}
	exec->fd_out = get_out_fd(command, env);
	if (exec->fd_out == -2 || exec->fd_out == -3)
	{
		if (exec->fd_in != -1)
			ft_close(exec->fd_in);
		error_exit_helper(exec->args, exec);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		close_pipes(char **args, t_executor *exec)
{
	if (exec->i > 0)
	{
		if (exec->pipe_prev[PIPE_IN] == -1 || exec->pipe_prev[PIPE_OUT] == -1)
			ft_printf("what no\n");
		ft_close(exec->pipe_prev[PIPE_IN]);
		ft_close(exec->pipe_prev[PIPE_OUT]);
		if (get_errno() == CLOSE_ERROR)
		{
			error_exit_helper(args, exec);
			return (EXIT_FAILURE);
		}
	}
	exec->pipe_prev[PIPE_IN] = exec->pipe_next[PIPE_IN];
	exec->pipe_prev[PIPE_OUT] = exec->pipe_next[PIPE_OUT];
	if (exec->fd_in > 2 && fstat(exec->fd_in, &exec->buf) == 0)
		ft_close(exec->fd_in);
	if (exec->fd_out > 2 && fstat(exec->fd_out, &exec->buf) == 0)
		ft_close(exec->fd_out);
	if (get_errno() == CLOSE_ERROR)
	{
		error_exit_helper(args, exec);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
