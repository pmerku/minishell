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

static int		exec_num_builtins()
{
	return (sizeof(builtin_str) / sizeof(char *));
}

static int		exec_launch(char **command, char *infile, char *outfile, int background)
{
	int		tmpin;
	int 	tmpout;

	int 	fdin;
	int		i;

	pid_t	pid;
	int 	fdout;

	tmpin = dup(0);
	tmpout = dup(1);

	if (infile != NULL) {
		fdin = open(infile, O_RDONLY);
	}
	else {
		fdin = dup(tmpin);
	}
	i = 0;
	while (i < exec_num_builtins()) {
		dup2(fdin, 0);
		close(fdin);
		if (i == exec_num_builtins() - 1) {
			if (outfile != NULL) {
				fdout = open(outfile, O_WRONLY);
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
		if (ft_strcmp(command[0], builtin_str[0]) == 0) {
			builtin_func[0](command);
		}
		pid = fork();
		if (pid == 0) {
			execve(command[0], command, NULL);
			strerror(EINTR);
			exit(EXIT_FAILURE);
		}
		else if (pid < 0) {
			exit(EXIT_FAILURE);
		}
		i++;
	}

	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);

	int status = 1;
	pid_t	wpid = pid;
	if (!background) {
		while (!WIFEXITED(status) && !WIFSIGNALED(status) && wpid)
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

int				execute(t_parser_command ***commands, t_env *env)
{
	t_parser_command	**list;
	t_parser_command	*command;
//	t_redirection		**redirections;
	size_t				i;
	char 				**command_args;
	char 				*parsed_string;

	command_args = (char **)ft_calloc(sizeof(char *), 2);
	list = *commands;
	command = *list;
	i = 0;
	while (command->arguments[i] != NULL) {
		parsed_string = env_parse_string(env, command->arguments[i]);
		command_args[i] = ft_strdup(parsed_string);
		ft_nullcheck(command_args[i]);
		ft_free(parsed_string);
		i++;
	}
	return (exec_launch(command_args, NULL, NULL, 0));
//	transform ***commands into **char
//	how to parse this fing no idea????

//	if (command->arguments->str == NULL)
//	{
//		return (1);
//	}
//	i = 0;
//	while (i < exec_num_buiiltins())
//	{
//		if (ft_strcmp(command->arguments->str[i], builtin_str[i] == 0))
//		{
//			return (*builtin_func(command->arguments->str[i])(command->arguments->str));
//		}
//		i++;
//	}
//	return (exec_launch(command));
}
