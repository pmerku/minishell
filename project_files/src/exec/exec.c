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

static int	exec_num_commands(t_parser_command ***commands)
{
	int i;

	i = 0;
	while (commands[i] != NULL)
	{
		i++;
	}
	return (i);
}

static char	**parse_args(t_parser_command *command, t_env *env)
{
	size_t	i;
	size_t	j;
	char	**arr;

	j = 0;
	i = 0;
	while (command->arguments[i] != NULL)
		i++;
	arr = ft_calloc(i + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (j < i)
	{
		arr[j] = env_parse_string(env, command->arguments[j]);
		if (arr[j] == NULL)
			return (ft_free_array(arr));
		j++;
	}
	return (arr);
}

/*
** Note to primoz; builtins are executed in forks if there's more than one
** command that's being executed (if you do `echo hello | exit 2`, exit will be
** called in a fork, not on the "main" process, and thus not exit anything).
**
** Fun, isn't it?
*/

void		exit_codes(t_executor *exec, t_env *env)
{
	while ((exec->last_pid = waitpid(0, &exec->status, WUNTRACED)) > 0)
	{
		if (exec->last_pid == exec->pid)
		{
			if (WIFEXITED(exec->status))
				env->last_status = WEXITSTATUS(exec->status);
			else if (WIFSIGNALED(exec->status))
			{
				env->last_status = WTERMSIG(exec->status);
				env->last_status += SIGNAL_TERMINATED;
			}
		}
	}
}

static int	loop_wrap(t_executor *exec, t_parser_command **list,
			t_parser_command *command, t_env *env)
{
	exec->args = parse_args(command, env);
	exec->built_in = 0;
	if (make_pipes(exec, list, command, env) == 1)
		return (1);
	if (list[1] == NULL)
		if (builtin_search(exec->args, exec, env, list[exec->i + 1]) != 0)
			return (1);
	return (0);
}

static int	exec_command_multiple(t_parser_command **list, t_env *env)
{
	t_executor			exec;
	t_parser_command	*command;

	if (list == NULL || list[0] == NULL)
		return (EXIT_SUCCESS);
	init_pipes(&exec);
	while (list[exec.i] != NULL)
	{
		command = list[exec.i];
		if (loop_wrap(&exec, list, command, env) == 1)
			break ;
		if (exec.built_in == 0)
			if (exec_fork(exec.args, &exec, env, list[exec.i + 1]) == 1)
				return (EXIT_FAILURE);
		if (close_pipes(exec.args, &exec) == 1)
			break ;
		exec.args = ft_free_array(exec.args);
		exec.i++;
	}
	exit_helper(exec.args, &exec);
	exit_codes(&exec, env);
	return (EXIT_SUCCESS);
}

int			execute(t_parser_command ***commands, t_env *env)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (i < exec_num_commands(commands))
	{
	    if (!(commands[i][0] != NULL && commands[i][1] == NULL && commands[i][0]->arguments == NULL))
            ret = exec_command_multiple(commands[i], env);
		i++;
	}
	return (ret);
}
