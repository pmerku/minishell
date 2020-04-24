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

static char		*builtin_str[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"
};

static int		(*builtin_func[8]) (char **) = {
		&exec_echo,
		&exec_cd,
		//&exec_pwd,
		//&exec_export,
		//&exec_unset,
		//&exec_env,
		&exec_exit
};

//static int		exec_num_builtins()
//{
//	return (sizeof(builtin_str) / sizeof(char *));
//}

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
	t_parser_command	*command;
	t_redirection		**redirections;
	t_simple_command	*simple_command;
	int 				i;

	command = *list;
	i = 0;
	while (command->arguments[i] != NULL) {
		i++;
	}
	simple_command = ft_checked_malloc(sizeof(t_simple_command));
	if (!simple_command) {
		return (NULL);
	}
	simple_command->args = (char **)ft_checked_calloc(i, sizeof(char *));
	if (!simple_command->args) {
		return (NULL);
	}
	i = 0;
	while (command->arguments[i] != NULL) {
		simple_command->args[i] = env_parse_string(env, command->arguments[i]);
		ft_printf("COMMAND ARGS ==> [%s]\n", simple_command->args[i]);
		i++; //TODO expand path (/bin/<command>)
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
	int		tmpin;
	int 	tmpout;

	int 	fdin;
	int		i;

	pid_t	pid;
	int 	fdout;

	tmpin = dup(0);
	tmpout = dup(1);

	t_simple_command	*simple_command = NULL;

	simple_command = exec_launch(list, env);
	if (!simple_command) {
		return (0);
	}
	if (simple_command->infile != NULL) {
		fdin = open(simple_command->infile, O_RDONLY);
	}
	else {
		fdin = dup(tmpin);
	}
	i = 0;
	ft_printf("NUM OF PIPES: [%d]\n", exec_num_simple_commands(list) - 1);
	while (i < exec_num_simple_commands(list)) {
		ft_printf("PIPE INDEX: [%d]\n", i);
		if (simple_command == NULL) {
			list++;
			simple_command = exec_launch(list, env);
		}
		dup2(fdin, 0);
		close(fdin);
		if (i == exec_num_simple_commands(list) - 1) {
			if (simple_command->outfile != NULL) {
				fdout = open(simple_command->outfile, O_WRONLY);
			}
			else {
				fdout = dup(tmpout);
			}
		}
		else {
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);
		if (ft_strcmp(simple_command->args[0], builtin_str[0]) == 0) {
			builtin_func[0](simple_command->args); //TODO
		}
		pid = fork();
		if (pid == 0) {
			execve(simple_command->args[0], simple_command->args, NULL);
			ft_printf("Something went wrong! (execve)\n");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0) {
			ft_printf("Something went wrong! (fork)\n");
			exit(EXIT_FAILURE);
		}
		ft_free(simple_command);
		simple_command = NULL;
		i++;
	}

	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);

	int		status = 1;
	int		background = 0; //TODO
	if (!background) {
		waitpid(pid, &status, WUNTRACED);
	}
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
		ft_printf("COMMAND ==> [%d]\n", i);
		ret = exec_command(commands[i], env);
		i++;
	}
	return (ret);
}
