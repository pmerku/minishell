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

static t_builtin_list g_builtin_list[] = {
		{"echo",   builtin_echo},
		{"cd",     builtin_cd},
		{"pwd",    builtin_pwd},
		{"export", builtin_export},
		{"unset",  builtin_unset},
		{"env",    builtin_env},
		{"exit",   builtin_exit},
};

static void ft_close(int fd)
{
	close(fd);
}

int exit_helper(char **args, t_executor *exec)
{
	if (args)
		ft_free_array(args);
	(void) exec;
	return (1);
}

static int exec_num_commands(t_parser_command ***commands)
{
	int i;

	i = 0;
	while (commands[i] != NULL)
	{
		i++;
	}
	return (i);
}

static char **parse_args(t_parser_command *command, t_env *env)
{
	size_t i;
	size_t j;
	char **arr;

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

static int get_in_fd(t_parser_command *command, t_env *env)
{
	size_t i;
	t_redirection *redir;
	char *file;
	int fd;

	if (command->redirections_in == NULL)
	{
		return (-1);
	}
	i = 0;
	while (command->redirections_in[i] != NULL)
	{
		redir = command->redirections_in[i];
		file = env_parse_string(env, redir->file);
		if (file == NULL)
			return (-2);
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			ft_printf("&cError opening file &f%s&c: &f%s&r\n", file,
					  strerror(errno));
			ft_free(file);
			return (-3);
		}
		ft_free(file);
		i++;
	}
	return (fd);
}

static int get_out_fd(t_parser_command *command, t_env *env)
{
	size_t i;
	t_redirection *redir;
	char *file;
	int fd;

	if (command->redirections_out == NULL)
	{
		return (-1);
	}
	i = 0;
	while (command->redirections_out[i] != NULL)
	{
		redir = command->redirections_out[i];
		file = env_parse_string(env, redir->file);
		if (file == NULL)
			return (-2);
		fd = open(file, O_WRONLY | O_CREAT |
						(redir->type == APPEND ? O_APPEND : O_TRUNC), 0644);
		if (fd == -1)
		{
			ft_printf("&cError opening file &f%s&c: &f%s&r\n", file,
					  strerror(errno));
			ft_free(file);
			return (-3);
		}
		ft_free(file);
		i++;
	}
	return (fd);
}

static void _signal_handler(int signo)
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

/*
** Note to primoz; builtins are executed in forks if there's more than one
** command that's being executed (if you do `echo hello | exit 2`, exit will be
** called in a fork, not on the "main" process, and thus not exit anything).
**
** Fun, isn't it?
*/

static int exec_command_multiple(t_parser_command **list, t_env *env)
{
	t_executor exec;
	t_parser_command *command;
	char **args;
	size_t i;

	i = 0;
	ft_bzero(&exec, sizeof(exec));
	if (list == NULL || list[0] == NULL)
		return (0);

	exec.pipe_prev[0] = -1;
	exec.pipe_prev[1] = -1;
	exec.pipe_next[0] = -1;
	exec.pipe_next[1] = -1;

	while (list[i] != NULL)
	{
		command = list[i];
		args = parse_args(command, env);

		if (list[1] != NULL && list[i + 1] != NULL && pipe(exec.pipe_next) != 0)
		{
			ft_printf("&cpipe error\n&r");
			// TODO Handle pipe error
			break;
		}

		int in_fd = get_in_fd(command, env);
		if (in_fd == -2 || in_fd == -3)
		{
			// TODO Handle error
			break;
		}
		int out_fd = get_out_fd(command, env);
		if (out_fd == -2 || out_fd == -3)
		{
			close(in_fd);
			// TODO Handle error
			break;
		}

		int builtin = 0;
		if (list[1] == NULL) {
			size_t j = 0;
			while (j < sizeof(g_builtin_list) / sizeof(g_builtin_list[0]))
			{
				if (ft_strcmp(args[0], g_builtin_list[j].name) == 0)
				{
					g_builtin_list[j].func(args, env);
					builtin = 1;
					break ;
				}
				j++;
			}
		}
		if (builtin == 0) {
			exec.pid = fork();
			if (exec.pid == 0)
			{
				signal(SIGINT, _signal_handler);
				signal(SIGQUIT, _signal_handler);

				if (out_fd >= 0)
				{
					dup2(out_fd, STANDARD_OUT);
					close(out_fd);
					if (list[i + 1] != NULL)
					{
						close(exec.pipe_next[PIPE_IN]);
						close(exec.pipe_next[PIPE_OUT]);
					}
				}
				else if (list[i + 1] != NULL)
				{
					dup2(exec.pipe_next[PIPE_OUT], STANDARD_OUT);
					close(exec.pipe_next[PIPE_IN]);
					close(exec.pipe_next[PIPE_OUT]);
				}
				if (in_fd >= 0)
				{
					dup2(in_fd, STANDARD_IN);
					close(in_fd);
					if (i != 0)
					{
						close(exec.pipe_prev[PIPE_IN]);
						close(exec.pipe_prev[PIPE_OUT]);
					}
				}
				else if (i != 0)
				{
					dup2(exec.pipe_prev[PIPE_IN], STANDARD_IN);
					close(exec.pipe_prev[PIPE_IN]);
					close(exec.pipe_prev[PIPE_OUT]);
				}
				size_t j = 0;
				while (j < sizeof(g_builtin_list) / sizeof(g_builtin_list[0]))
				{
					if (ft_strcmp(args[0], g_builtin_list[j].name) == 0)
					{
						g_builtin_list[j].func(args, env);
						exit(EXIT_SUCCESS);
					}
					j++;
				}
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
			else if (exec.pid < 0)
			{
				ft_printf("&cFork error\n&r");
				return (exit_helper(args, &exec));
			}
		}

		if (i > 0)
		{
			if (exec.pipe_prev[0] == -1 || exec.pipe_prev[1] == -1)
			{
				ft_printf("what no\n");
			}

			ft_close(exec.pipe_prev[0]);
			ft_close(exec.pipe_prev[1]);
		}

		exec.pipe_prev[0] = exec.pipe_next[0];
		exec.pipe_prev[1] = exec.pipe_next[1];

		if (in_fd >= 0)
			close(in_fd);
		if (out_fd >= 0)
			close(out_fd);

		ft_free_array(args);
		args = NULL;
		i++;
	}

//	ft_printf("&aFDs: &e%d&a, &e%d&a, &e%d&a, &e%d&a\n&r", exec.pipe_prev[0],
//			  exec.pipe_prev[1], exec.pipe_next[0], exec.pipe_next[1]);

	exit_helper(args, &exec);
	int last_pid;
	while ((last_pid = waitpid(0, &exec.status, WUNTRACED)) > 0)
	{
		if (last_pid == exec.pid)
		{
			if (WIFEXITED(exec.status))
				env->last_status = WEXITSTATUS(exec.status);
			else if (WIFSIGNALED(exec.status))
			{
				env->last_status = WTERMSIG(exec.status);
				env->last_status += SIGNAL_TERMINATED;
			}
		}
	}
	return (EXIT_SUCCESS);
}

int execute(t_parser_command ***commands, t_env *env)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (i < exec_num_commands(commands))
	{
		ret = exec_command_multiple(commands[i], env);
		i++;
	}
	return (ret);
}
