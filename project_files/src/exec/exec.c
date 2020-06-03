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

//static int 		exec_num_simple_commands(t_parser_command **list)
//{
//	int 	i;
//
//	i = 0;
//	while (list[i] != NULL) {
//		i++;
//	}
//	return (i);
//}

static int 		exec_num_commands(t_parser_command ***commands)
{
	int 	i;

	i = 0;
	while (commands[i] != NULL) {
		i++;
	}
	return (i);
}

static char 				**parse_args(t_parser_command *command, t_env *env)
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

//static t_simple_command 	*exec_launch(t_parser_command **list, t_env *env)
//{
////yeet	ft_printf("working on %p\n", list);
//	t_parser_command	*command;
//	t_redirection		**redirections;
//	t_simple_command	*simple_command;
//	int 				i;
//
//	command = *list;
//	i = 0;
//	while (command->arguments[i] != NULL) {
//		i++;
//	}
//	simple_command = ft_checked_calloc(1, sizeof(t_simple_command));
//	if (!simple_command) {
//		return (NULL);
//	}
//	simple_command->args = (char **)ft_checked_calloc(i + 1, sizeof(char *));
//	if (!simple_command->args) {
//		return (NULL);
//	}
//	i = 0;
//	while (command->arguments[i] != NULL) {
//		simple_command->args[i] = env_parse_string(env, command->arguments[i]);
//		//yeet	ft_printf("COMMAND ARGS ==> [%s]\n", simple_command->args[i]);
//		i++;
//	}
//	i = 0;
//	redirections = command->redirections_in;
//	while (redirections != NULL && redirections[i] != NULL) {
//		i++;
//	}
//	if (redirections != NULL && redirections[i - 1] != NULL) {
//		simple_command->infile = env_parse_string(env, redirections[i - 1]->file);
//		//yeet	ft_printf("INFILE ==> [%s]\n", simple_command->infile);
//	}
//	i = 0;
//	redirections = command->redirections_out;
//	while (redirections != NULL && redirections[i] != NULL) {
//		i++;
//	}
//	if (redirections != NULL && redirections[i - 1] != NULL) {
//		simple_command->outfile = env_parse_string(env, redirections[i - 1]->file);
//		simple_command->type= redirections[i - 1]->type;
//		//yeet	ft_printf("OUTFILE ==> [%s]\n", simple_command->outfile);
//	}
//	return (simple_command);
//}

static int 		get_input(t_parser_command *command, t_executor *exec, t_env *env, int prev_fd)
{
	size_t			i;
	t_redirection	*redir;
	char 			*file;

	(void)prev_fd;
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
			// TODO Probably close `exec->fd_in` ?
			ft_free(file);
			return (1);
		}
		ft_free(file);
		i++;
	}
	return (0);
}

static int 		get_output(t_parser_command *command, t_executor *exec, t_env *env, int last_command)
{
	size_t			i;
	t_redirection	*redir;
	char 			*file;

	i = 0;
	if (command->redirections_out == NULL)
	{
		pipe(exec->fd_pipe); // TODO Protect this
		exec->fd_out = exec->fd_pipe[1];
		exec->fd_in = exec->fd_pipe[0];
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
			// TODO Probably close `exec->fd_out` ?
			ft_free(file);
			return (1);
		}
		ft_free(file);
		i++;
	}
	return (0);
}

static int		exec_command2(t_parser_command **list, t_env *env)
{
	t_executor			exec;
	t_parser_command 	*command;
	char 				**args;
	size_t				i;
	int 				err;

	i = 0;
	ft_bzero(&exec, sizeof(exec));
	if (list == NULL || list[0] == NULL)
		return (0);

	exec.tmp_in = dup(0);
	exec.tmp_out = dup(1);

	while (list[i] != NULL)
	{
		command = list[i];
		args = parse_args(command, env);
		if (args == NULL)
		{
			ft_printf("&cFailed to parse args with env vars\n&r");
			// TODO Clean up any opened pipes / unfreed memory
			return (1);
		}
		err = get_input(command, &exec, env, i == 0 ? exec.tmp_in : exec.fd_out);
		if (err != 0)
		{
			// TODO Clean up any opened pipes / unfreed memory
			return (err);
		}
		err = get_output(command, &exec, env, list[i + 1] == NULL);
		if (err != 0)
		{
			// TODO Clean up any opened pipes / unfreed memory
			return (err);
		}
		dup2(exec.fd_out, 1);
		close(exec.fd_out);
		dup2(exec.fd_in, 0);
		close(exec.fd_in);
		// TODO Handle logic
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
				// TODO Clean up any opened pipes / unfreed memory
				return (1);
			}
		}
		i++;
	}

	dup2(exec.tmp_in, 0);
	dup2(exec.tmp_out, 1);
	close(exec.tmp_in);
	close(exec.tmp_out);

	exec.status = 0;
	waitpid(exec.pid, &exec.status, WUNTRACED);
	return (WEXITSTATUS(exec.status));
}

//static int		exec_command(t_parser_command **list, t_env *env)
//{
//	t_executor			exec;
//	t_simple_command	*simple_command;
//	int		i;
//	int		list_size;
//
//	exec.tmp_in = dup(0);
//	exec.tmp_out = dup(1);
//
//	simple_command = exec_launch(list, env);
//	if (!simple_command) {
//		return (0);
//	}
//
//	if (simple_command->infile != NULL) {
//		exec.fd_in = open(simple_command->infile, O_RDONLY);
//		if (exec.fd_in == -1) {
//			ft_printf("&cError opening file &f%s&c: &f%s&r\n", simple_command->infile, strerror(errno));
//			return (1);
//			// TODO Clean up properly
//		}
//	}
//	else {
//		exec.fd_in = dup(exec.tmp_in);
//	}
//	i = 0;
//	list_size = exec_num_simple_commands(list);
//	//yeet	ft_printf("NUM OF PIPES: [%d]\n", list_size - 1);
//	while (i < list_size) {
//		//yeet	ft_printf("PIPE INDEX: [%d]\n", i);
//		if (simple_command == NULL) {
//			list++;
//			simple_command = exec_launch(list, env);
//		}
//		dup2(exec.fd_in, 0);
//		close(exec.fd_in);
//		if (i == list_size - 1) {
//			if (simple_command->outfile != NULL) {
//				exec.fd_out = open(simple_command->outfile, O_WRONLY | O_CREAT | (simple_command->type == APPEND ? O_APPEND : O_TRUNC), 0664);
//				if (exec.fd_out == -1) {
//					ft_printf("&cError opening file &f%s&c: &f%s&r\n", simple_command->outfile, strerror(errno));
//					// TODO Close shit properly
//					return (1);
//				}
//			}
//			else {
//				exec.fd_out = dup(exec.tmp_out);
//			}
//		}
//		else {
//			pipe(exec.fd_pipe);
//			exec.fd_out = exec.fd_pipe[1];
//			exec.fd_in = exec.fd_pipe[0];
//		}
//		dup2(exec.fd_out, 1);
//		close(exec.fd_out);
//		size_t j = 0;
//		int builtin = 0;
//		while (j < sizeof(g_builtin_list) / sizeof(g_builtin_list[0])) {
//			if (ft_strcmp(simple_command->args[0], g_builtin_list[j].name) == 0) {
//				g_builtin_list[j].func(simple_command->args, env);
//				builtin = 1;
//				break ;
//			}
//			j++;
//		}
//		if (builtin == 0)
//		{
//			exec.pid = fork();
//			if (exec.pid == 0)
//			{
//				char *path = env_resolve_path_file(env, simple_command->args[0]);
//				if (path == NULL)
//				{
//					ft_printf("&cCommand not found: &f%s\n", simple_command->args[0]);
//					exit(EXIT_FAILURE);
//				}
//				execve(path, simple_command->args, env->vars);
//				ft_printf("Something went wrong! (execve) %s\n", strerror(errno));
//				exit(EXIT_FAILURE);
//			}
//			else if (exec.pid < 0)
//			{
//				ft_printf("Something went wrong! (fork)\n");
//				exit(EXIT_FAILURE);
//			}
//		}
//		ft_free(simple_command);
//		simple_command = NULL;
//		i++;
//	}
//
//	dup2(exec.tmp_in, 0);
//	dup2(exec.tmp_out, 1);
//	close(exec.tmp_in);
//	close(exec.tmp_out);
//
//	exec.status = 0;
//	waitpid(exec.pid, &exec.status, WUNTRACED);
//	return (WEXITSTATUS(exec.status));
//}

int				execute(t_parser_command ***commands, t_env *env)
{
	int 				i;
	int 				ret;

	i = 0;
	ret = 1;
	//yeet	ft_printf("\nNUM OF COMMANDS: [%d]\n", exec_num_commands(commands));
	while (i < exec_num_commands(commands)) {
		//yeet	ft_printf("  COMMAND ==> [%d]\n", i);
		ret = exec_command2(commands[i], env);
		i++;
	}
	return (ret);
}
