/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/26 00:00:00 by anonymous     #+#    #+#                 */
/*   Updated: 2020/08/26 00:00:00 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_stdio/ft_printf.h>
#include <unistd.h>
#include <ft_string.h>
#include <ft_env.h>
#include <stdlib.h>

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
