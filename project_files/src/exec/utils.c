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

#include <sys/types.h>
#include <stdlib.h>
#include <ft_exec.h>
#include <fcntl.h>
#include <ft_memory.h>
#include <utils.h>

int		error_exit_helper(char **args, t_executor *exec)
{
	struct stat	buf;

	if (fstat(exec->pipe_prev[PIPE_IN], &buf) == 0)
		ft_close(exec->pipe_prev[PIPE_IN]);
	if (fstat(exec->pipe_prev[PIPE_OUT], &buf) == 0)
		ft_close(exec->pipe_prev[PIPE_OUT]);
	if (fstat(exec->pipe_next[PIPE_IN], &buf) == 0)
		ft_close(exec->pipe_next[PIPE_IN]);
	if (fstat(exec->pipe_next[PIPE_OUT], &buf) == 0)
		ft_close(exec->pipe_next[PIPE_OUT]);
	if (exec->fd_in > 2 && fstat(exec->fd_in, &buf) == 0)
		ft_close(exec->fd_in);
	if (exec->fd_out > 2 && fstat(exec->fd_out, &buf) == 0)
		ft_close(exec->fd_out);
	(void)args;
	return (EXIT_FAILURE);
}

int		exit_helper(char **args, t_executor *exec)
{
	if (args)
		args = ft_free_array(args);
	(void)exec;
	return (EXIT_FAILURE);
}
