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

#include <ft_env.h>
#include <stdlib.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <ft_stdio/ft_printf.h>

static int	int_len(int n)
{
	int len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

int			builtin_exit(char **args, t_env *env)
{
	int		status;

	ft_printf("exit\n");
	status = env->last_status;
	if (args[1] != NULL)
	{
		status = ft_atoi(args[1]);
		if (ft_strlen(args[1]) != (size_t)int_len(status))
		{
			if (ft_printf("&cError: &rInvalid exit code provided\n") == -1)
				exit(1);
			exit(128);
		}
		if (status < 0 || status > 255)
		{
			exit(255);
		}
	}
	exit(status);
}
