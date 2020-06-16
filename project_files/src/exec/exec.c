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

static t_builtin_list	g_builtin_list[] = {
		{"echo", builtin_echo},
		{"cd", builtin_cd},
		{"pwd", builtin_pwd},
		{"export", builtin_export},
		{"unset", builtin_unset},
		{"env", builtin_env},
		{"exit", builtin_exit},
};

int						exit_helper(char **args, t_executor *exec)
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

static int 				exec_num_commands(t_parser_command ***commands)
{
	int 	i;

	i = 0;
	while (commands[i] != NULL) {
		i++;
	}
	return (i);
}

static char 			**parse_args(t_parser_command *command, t_env *env)
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

static int 				get_input(t_parser_command *command, t_executor *exec, t_env *env, int prev_fd)
{
	size_t			i;
	t_redirection	*redir;
	char 			*file;

	i = 0;
	if (command->redirections_in == NULL)
	{
		exec->fd_in = dup(prev_fd);
		return (0);
	}
	exec->fd_in = -1;
	while (command->redirections_in[i] != NULL)
	{
		redir = command->redirections_in[i];
		if (exec->fd_in != -1)
			close(exec->fd_in);
		file = env_parse_string(env, redir->file);
		if (file == NULL)
			return (1);
		exec->fd_in = open(file, O_RDONLY);
		if (exec->fd_in == -1) {
			ft_printf("&cError opening file &f%s&c: &f%s&r\n", file, strerror(errno));
			ft_free(file);
			return (1);
		}
		ft_free(file);
		i++;
	}
	return (0);
}

static int 				get_output(t_parser_command *command, t_executor *exec, t_env *env, int last_command)
{
	size_t			i;
	t_redirection	*redir;
	char 			*file;

	i = 0;
	if (command->redirections_out == NULL)
	{
		if (pipe(exec->fd_pipe) == -1)
		{
			ft_printf("&cFailed to create pipes\n&r");
			return(1);
		}
		exec->fd_in = exec->fd_pipe[PIPE_IN];
		exec->fd_out = exec->fd_pipe[PIPE_OUT];
		if (last_command)
		{
			close(exec->fd_out);
			exec->fd_out = exec->tmp_out;
		}
		return (0);
	}
	exec->fd_out = -1;
	while (command->redirections_out[i] != NULL)
	{
		redir = command->redirections_out[i];
		if (exec->fd_out != -1)
			close(exec->fd_out);
		file = env_parse_string(env, redir->file);
		if (file == NULL)
			return (1);
		exec->fd_out = open(file, O_WRONLY | O_CREAT | (redir->type == APPEND ? O_APPEND : O_TRUNC), 0644);
		if (exec->fd_out == -1)
		{
			ft_printf("&cError opening file &f%s&c: &f%s&r\n", file, strerror(errno));
			ft_free(file);
			return (1);
		}
		ft_free(file);
		i++;
	}
	return (0);
}

static int				exec_command(t_parser_command **list, t_env *env)
{
	t_executor			exec;
	t_parser_command 	*command;
	char 				**args;
	size_t				i;

	i = 0;
	ft_bzero(&exec, sizeof(exec));
	if (list == NULL || list[0] == NULL)
		return (0);

	exec.tmp_in = dup(STANDARD_IN);
	exec.tmp_out = dup(STANDARD_OUT);
	while (list[i] != NULL)
	{
		command = list[i];
		args = parse_args(command, env);
		dup2(exec.fd_in, STANDARD_IN);
		close(exec.fd_in);
		if (args == NULL)
		{
			ft_printf("&cFailed to parse args with env vars\n&r");
			return (exit_helper(args, &exec));
		}
		if (get_input(command, &exec, env, i == 0 ? exec.tmp_in : exec.fd_out) != 0)
			return (exit_helper(args, &exec));
		if (get_output(command, &exec, env, list[i + 1] == NULL) != 0)
			return (exit_helper(args, &exec));
		dup2(exec.fd_out, STANDARD_OUT);
		close(exec.fd_out);
		size_t j = 0;
		int builtin = 0;
		while (j < sizeof(g_builtin_list) / sizeof(g_builtin_list[0])) {
			if (ft_strcmp(args[0], g_builtin_list[j].name) == 0) {
				g_builtin_list[j].func(args, env);
				builtin = 1;
				break ;
			}
			j++;
		}
		if (builtin == 0)
		{
			exec.pid = fork();
			if (exec.pid == 0)
			{
				char *path = env_resolve_path_file(env, args[0]);
				if (path == NULL)
				{
					ft_printf("&cCommand not found: &f%s\n", args[0]);
					exit(EXIT_FAILURE);
				}
				execve(path, args, env->vars);
				ft_printf("&cExecve error: &r%s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			else if (exec.pid < 0)
			{
				ft_printf("&cFork error\n&r");
				return (exit_helper(args, &exec));
			}
		}
		ft_free_array(args);
		args = NULL;
		i++;
	}
	exit_helper(args, &exec);

	exec.status = 0;
	waitpid(exec.pid, &exec.status, WUNTRACED);
	return (WEXITSTATUS(exec.status));
}

int						execute(t_parser_command ***commands, t_env *env)
{
	int 				i;
	int 				ret;

	i = 0;
	ret = 0;
	while (i < exec_num_commands(commands)) {
		ret = exec_command(commands[i], env);
		i++;
	}
	return (ret);
}
