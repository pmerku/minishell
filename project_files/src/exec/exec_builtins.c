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

int 	exec_exit(char **args)
{
	return (0);
}

int		exec_cd(char **args)
{
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

int 	exec_echo(char **args)
{
	if (args[1] == NULL)
	{
		ft_printf("\n");
	}
	else
	{
		if (ft_strcmp(args[1], "-n") == 0)
			return (1);
		else
			ft_printf("%s\n", args[1]);
	}
}