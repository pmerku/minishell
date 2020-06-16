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
#include <ft_string.h>
#include <ft_env.h>

int 	builtin_echo(char **args, t_env *env)
{
	(void)	env;
	int		print_newline;
	size_t	i;

	print_newline = args[1] == NULL ? 1 : ft_strcmp(args[1], "-n") != 0;
	i = 2 - print_newline;
	while (args[i] != NULL)
	{
		if (ft_printf("%s%s", args[i], args[i + 1] == NULL ? "" : " ") == 1)
			return (1);
		i++;
	}
	return ((print_newline && ft_printf("\n") == -1) ? 1 : 0);
}
