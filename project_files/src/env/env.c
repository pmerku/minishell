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

#include <ft_string.h>
#include <ft_env.h>
#include <ft_memory.h>
#include <ft_stdio/ft_printf.h>

t_env		*env_from(char **envp)
{
	t_env	*env;
	size_t	i;

	i = 0;
	env = ft_checked_malloc(sizeof(t_env));
	env->vars = ft_checked_malloc(sizeof(char *) * (1 + ft_strarr_size(envp)));
	while (envp[i] != NULL)
	{
		env->vars[i] = ft_nullcheck(ft_strdup(envp[i]));
		i++;
	}
	envp[i] = NULL;
	return (env);
}

static char	*match_key(char *pair, char *key)
{
	size_t i;

	i = 0;
	while (pair[i] == key[i] && pair[i] && key[i] && pair[i] != '=')
		i++;
	if (key[i] == '\0' && pair[i] == '=')
		return (pair + i + 1);
	return (NULL);
}

void		env_set(t_env *env, char *key, char *value)
{
	size_t	i;

	if (key == NULL || value == NULL)
		ft_eprintf(1, "Attempted to set NULL env var (k, v): '%s', '%s'",
				key, value);
	i = 0;
	while (env->vars[i] != NULL)
	{
		if (match_key(env->vars[i], key) != NULL)
		{
			ft_free(env->vars[i]);
			env->vars[i] = ft_strjoin3(key, "=", value);
			return ;
		}
		i++;
	}
	ft_strarr_append(&env->vars, ft_strjoin3(key, "=", value));
}

void		env_remove(t_env *env, char *key)
{
	size_t	i;
	char	removed;

	i = 0;
	removed = 0;
	while (env->vars[i] != NULL)
	{
		if (match_key(env->vars[i], key) != NULL)
		{
			ft_free(env->vars[i]);
			removed = 1;
		}
		if (removed)
			env->vars[i] = env->vars[i + 1];
		i++;
	}
}

char		*env_get(t_env *env, char *key)
{
	char	**vars;
	char	*match;

	vars = env->vars;
	while (*vars != NULL)
	{
		match = match_key(*vars, key);
		if (match != NULL)
			return (match);
		vars++;
	}
	return ("");
}
