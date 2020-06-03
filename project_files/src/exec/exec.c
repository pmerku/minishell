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
//	{"echo", builtin_echo}, <== Binary exists
	{"cd", builtin_cd},
//	{"pwd", builtin_pwd}, <== Binary exists
//	{"export", builtin_export},
//	{"unset", builtin_unset},
//	{"env", builtin_env},
	{"exit", builtin_exit},
};

static int 		exec_num_simple_commands(t_parser_command **list)
{
	int 	i;

	i = 0;
	while (list[i] != NULL) {
		i++;
	}
	return (i);
}

static int 		exec_num_commands(t_parser_command ***commands)
{
	int 	i;

	i = 0;
	while (commands[i] != NULL) {
		i++;
	}
	return (i);
}

static t_simple_command 	*exec_launch(t_parser_command **list, t_env *env)
{
	ft_printf("working on %p\n", list);
	t_parser_command	*command;
	t_redirection		**redirections;
	t_simple_command	*simple_command;
	int 				i;

	command = *list;
	i = 0;
	while (command->arguments[i] != NULL) {
		i++;
	}
	simple_command = ft_checked_calloc(1, sizeof(t_simple_command));
	if (!simple_command) {
		return (NULL);
	}
	simple_command->args = (char **)ft_checked_calloc(i + 1, sizeof(char *));
	if (!simple_command->args) {
		return (NULL);
	}
	i = 0;
	while (command->arguments[i] != NULL) {
		simple_command->args[i] = env_parse_string(env, command->arguments[i]);
		ft_printf("COMMAND ARGS ==> [%s]\n", simple_command->args[i]);
		i++;
	}
	i = 0;
	redirections = command->redirections_in;
	while (redirections != NULL && redirections[i] != NULL) {
		i++;
	}
	if (redirections != NULL && redirections[i - 1] != NULL) {
		simple_command->infile = env_parse_string(env, redirections[i - 1]->file);
		ft_printf("INFILE ==> [%s]\n", simple_command->infile);
	}
	i = 0;
	redirections = command->redirections_out;
	while (redirections != NULL && redirections[i] != NULL) {
		i++;
	}
	if (redirections != NULL && redirections[i - 1] != NULL) {
		simple_command->outfile = env_parse_string(env, redirections[i - 1]->file);
		ft_printf("OUTFILE ==> [%s]\n", simple_command->outfile);
	}
	return (simple_command);
}

static int		exec_command(t_parser_command **list, t_env *env)
{
	t_executor			exec;
	t_simple_command	*simple_command;
	int		i;
	int		list_size;

	exec.tmp_in = dup(0);
	exec.tmp_out = dup(1);

	simple_command = exec_launch(list, env);
	if (!simple_command) {
		return (0);
	}
	if (simple_command->infile != NULL) {
		exec.fd_in = open(simple_command->infile, O_RDONLY);
		if (exec.fd_in == -1) {
			ft_printf("&cError opening file &f%s&c: &f%s&r\n", simple_command->infile, strerror(errno));
			return (1);
			// TODO Clean up properly
		}
	}
	else {
		exec.fd_in = dup(exec.tmp_in);
	}
	i = 0;
	list_size = exec_num_simple_commands(list);
	ft_printf("NUM OF PIPES: [%d]\n", list_size - 1);
	while (i < list_size) {
		ft_printf("PIPE INDEX: [%d]\n", i);
		if (simple_command == NULL) {
			list++;
			simple_command = exec_launch(list, env);
		}
		dup2(exec.fd_in, 0);
		close(exec.fd_in);
		if (i == list_size - 1) {
			if (simple_command->outfile != NULL) {
				exec.fd_out = open(simple_command->outfile, O_WRONLY);
			}
			else {
				exec.fd_out = dup(exec.tmp_out);
			}
		}
		else {
			pipe(exec.fd_pipe);
			exec.fd_out = exec.fd_pipe[1];
			exec.fd_in = exec.fd_pipe[0];
		}
		dup2(exec.fd_out, 1);
		close(exec.fd_out);
		size_t j = 0;
		while (j < sizeof(g_builtin_list) / sizeof(g_builtin_list[0])) {
			if (ft_strcmp(simple_command->args[0], g_builtin_list[j].name) == 0) {
				g_builtin_list[j].func(simple_command->args, env);
				break ;
//				return ((struct s_program){
//						.type = BUILTIN,
//						.builtin_func = g_builtin_map[i].func,
//				});
			}
			j++;
		}
		exec.pid = fork();
		if (exec.pid == 0) {
			char *path = env_resolve_path_file(env, simple_command->args[0]);
			if (path == NULL) {
				ft_printf("Command not found: %s\n", simple_command->args[0]);
//				exit(EXIT_FAILURE);
				return (0);
			}
			ft_printf("Executing command: %s\n", path);
			ft_printf("args: %p\n", simple_command->args);
			j = 0;
			while (simple_command->args[j] != NULL) {
				ft_printf(" arg: '%s'\n", simple_command->args[j]);
				j++;
			}
			execve(path, simple_command->args, env->vars);
			ft_printf("Something went wrong! (execve) %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		else if (exec.pid < 0) {
			ft_printf("Something went wrong! (fork)\n");
			exit(EXIT_FAILURE);
		}
		ft_free(simple_command);
		simple_command = NULL;
		i++;
	}

	dup2(exec.tmp_in, 0);
	dup2(exec.tmp_out, 1);
	close(exec.tmp_in);
	close(exec.tmp_out);

	exec.status = 1;
	waitpid(exec.pid, &exec.status, WUNTRACED);
	return (1);
}

int				execute(t_parser_command ***commands, t_env *env)
{
	int 				i;
	int 				ret;

	i = 0;
	ret = 1;
	ft_printf("\nNUM OF COMMANDS: [%d]\n", exec_num_commands(commands));
	while (i < exec_num_commands(commands) && ret == 1) {
		ft_printf("  COMMAND ==> [%d]\n", i);
		ret = exec_command(commands[i], env);
		i++;
	}
	return (ret);
}
