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
#include <stdio.h>
#include <unistd.h>
#include <ft_string.h>
#include <ft_env.h>
#include <stdlib.h>

int 	builtin_exit(char **args, t_env *env)
{
	(void)args;
	(void)env;
	exit(0);
}

int		builtin_cd(char **args, t_env *env)
{
	(void)env;
	if (args[1] == NULL)
	{
		ft_fprintf(2, "Exec: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("lsh");
		}
	}
	return (1);
}

int 	builtin_echo(char **args, t_env *env)
{
	(void)env;
	int		print_newline;
	size_t 	i;

	print_newline = args[1] == NULL ? 1 : ft_strcmp(args[1], "-n") != 0;
	i = print_newline ? 1 : 2;
	while (args[i] != NULL)
	{
		if (ft_printf("%s%s", args[i], args[i + 1] == NULL ? "" : " ") == 1)
			return (1);
		i++;
	}
	if (print_newline)
		if (ft_printf("\n") == -1)
			return (1);
	return (0);
}

// echo -n hello > out ; echo test | cat -e < out > in
// echo -n > out ; echo test | cat -e < out > in