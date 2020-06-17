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
