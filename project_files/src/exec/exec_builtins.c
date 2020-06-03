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

int		builtin_pwd(char **args, t_env *env)
{
	char *pwd;

	(void)args;
	(void)env;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_fprintf(2, "&cFailed to get current working directory.\n&r");
		return (1);
	}
	if (ft_printf("%s\n", pwd) == -1)
		return (1);
	free(pwd);
	return (0);
}

int		builtin_export(char **args, t_env *env)
{
	size_t	i;

	if (args[1] == NULL)
	{
		ft_printf("&cThis is not a feature we *have* to support...\n&r");
		return (0);
	}
	i = 0;
	while (args[1][i] != '\0' && args[1][i] != '=')
		i++;
	if (args[1][i] == '\0')
		return (0);
	args[1][i] = '\0';
	env_set(env, args[1], args[1] + i + 1);
	return (0);
}

int		builtin_unset(char **args, t_env *env)
{
	if (args[1] == NULL)
		return (0);
	env_remove(env, args[1]);
	return (0);
}

int		builtin_env(char **args, t_env *env)
{
	size_t i;

	(void)args;
	i = 0;
	while (env->vars[i] != NULL)
	{
		if (ft_printf("%s\n", env->vars[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

// echo -n hello > out ; echo test | cat -e < out > in
// echo -n > out ; echo test | cat -e < out > in