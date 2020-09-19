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

#include <ft_parser.h>
#include <ft_env.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ft_exec.h>
#include <ft_string.h>
#include <builtins.h>
#include <ft_errno.h>
#include <utils.h>

static t_builtin_list	g_builtin_list[] = {
	{"", builtin_empty},
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit}
};

static int				fd_out_handler(char **args, t_executor *exec,
						t_parser_command *list)
{
	if (exec->fd_out >= 0)
	{
		if (ft_dup2(exec->fd_out, STANDARD_OUT) == -1)
			return (error_exit_helper(args, exec));
		ft_close(exec->fd_out);
		if (list != NULL)
		{
			ft_close(exec->pipe_next[PIPE_IN]);
			ft_close(exec->pipe_next[PIPE_OUT]);
		}
		if (get_errno() == CLOSE_ERROR)
			return (error_exit_helper(args, exec));
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

int						builtin_search(char **args, t_executor *exec,
						t_env *env, t_parser_command *list)
{
	size_t j;

	j = 0;
	while (j < sizeof(g_builtin_list) / sizeof(g_builtin_list[0]))
	{
		if (ft_strcmp(args[0], g_builtin_list[j].name) == 0)
		{
			exec->built_in = 1;
			exec->fd_tmp_out = ft_dup(STANDARD_OUT);
			exec->fd_tmp_in = ft_dup(STANDARD_OUT);
			if (exec->fd_tmp_out == -1 || exec->fd_tmp_in == -1)
				return (error_exit_helper(args, exec));
			if (fd_out_handler(args, exec, list) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			g_builtin_list[j].func(args, env);
			if (ft_dup2(exec->fd_tmp_out, STANDARD_OUT) == -1
				|| ft_dup2(exec->fd_tmp_in, STANDARD_IN) == -1)
				return (error_exit_helper(args, exec));
			ft_close(exec->fd_tmp_out);
			ft_close(exec->fd_tmp_in);
			if (get_errno() == CLOSE_ERROR)
				return (error_exit_helper(args, exec));
			break ;
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

int						f_builtin_search(char **args, t_env *env)
{
	size_t j;

	j = 0;
	while (j < sizeof(g_builtin_list) / sizeof(g_builtin_list[0]))
	{
		if (ft_strcmp(args[0], g_builtin_list[j].name) == 0)
		{
			g_builtin_list[j].func(args, env);
			exit(EXIT_SUCCESS);
		}
		j++;
	}
	return (EXIT_SUCCESS);
}
