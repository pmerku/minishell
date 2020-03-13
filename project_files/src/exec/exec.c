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
#include <sys/types.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <ft_exec.h>

static char		*builtin_str[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"
};

static int		(*builtin_func[]) (char **) = {
		&exec_echo,
		&exec_cd,
		&exec_pwd,
		&exec_export,
		&exec_unset,
		&exec_env,
		&exec_exit
}

static int		exec_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char *);
}

static int		exec_launch(t_parser_command *command)
{
	pid_t	pid;
	pid_t	wpid;
	int 	status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(command->arguments, command) == -1)
		{
			perror("Executor");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Executor");
	}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}

	return (1);
}

int				execute(t_parser_command *command)
{
	int 	i;

	if (command->arguments == NULL)
	{
		return (1);
	}
	i = 0;
	while (i < exec_num_buiiltins())
	{
		if (ft_strcmp(command->arguments, builtin_str[i] == 0))
		{
			return (*builtin_func(command->arguments[i])(command->arguments));
		}
		i++;
	}
	return (exec_launch(command));
}
