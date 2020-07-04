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

#include <ft_parser.h>
#include <ft_env.h>
#include <sys/types.h>
#include <zconf.h>
#include <ft_exec.h>
#include <ft_string.h>
#include <ft_memory.h>

int 		exec_num_commands(t_parser_command ***commands)
{
	int 	i;

	i = 0;
	while (commands[i] != NULL) {
		i++;
	}
	return (i);
}

char		**parse_args(t_parser_command *command, t_env *env)
{
	size_t		i;
	size_t 		j;
	char 		**arr;

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

int			exit_helper(char **args, t_executor *exec)
{
	if (args)
		ft_free_array(args);
	if (exec->fd_pipe[PIPE_IN])
		close(exec->fd_pipe[PIPE_IN]);
	if (exec->fd_pipe[PIPE_OUT])
		close(exec->fd_pipe[PIPE_OUT]);
	if (exec->fd_in)
		close(exec->fd_in);
	if (exec->fd_out)
		close(exec->fd_out);
	dup2(exec->tmp_in, STANDARD_IN);
	dup2(exec->tmp_out, STANDARD_OUT);
	close(exec->tmp_in);
	close(exec->tmp_out);
	return (1);
}