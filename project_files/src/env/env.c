/* ************************************************************************** */
/*                                                                            */
/*   Project: project_files                               ::::::::            */
/*   Members: dvoort, prmerku                           :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_env.h>
#include <libft.h>
#include <memmgmt.h>
#include <printf.h>
#include <zconf.h>
#include <stdlib.h>
#include <sys/stat.h>

t_env		*env_from(char **envp)
{
	char 	**parts;
	t_env	*env;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		parts = ft_nsplit(envp[i], '=', 2);
		if (ft_strarr_size(parts) == 1 && !ft_strends_with(envp[i], "="))
			ft_eprintf(1, "Invalid environmental variable %s\n", envp[i]);
		if (parts[1] == NULL)
			env_set(&env, parts[0], ft_strdup(""));
		else
			env_set(&env, parts[0], parts[1]);
		i++;
	}
	return (env);
}

void		env_set(t_env **env, char *key, char *value)
{
	t_env *new_elem;

	if (key == NULL || value == NULL)
		ft_eprintf(1, "Attempted to set NULL env var (k, v): '%s', '%s'",
				key, value);
	new_elem = ft_checked_malloc(sizeof(t_env));
	new_elem->next = *env;
	new_elem->key = key;
	new_elem->value = value;
	*env = new_elem;
}

void		env_print_all(t_env *env)
{
	ft_printf("&b&l&n%-20s &f= &b&l%-50s&r\n", "Key", "Value");
	while (env != NULL)
	{
		ft_printf("&b%-20s &r= %s\n", env->key, env->value);
		env = env->next;
	}
}

char 		*env_get(t_env *env, char *key)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*compound_to_string(t_env *env, t_compound_string *string)
{
	char *env_value;

	if (string->type == STRING)
	{
		return (string->str);
	}
	else
	{
		env_value = env_get(env, string->str);
		return (env_value == NULL ? "" : env_value);
	}
}

char		*env_parse_string(t_env *env, t_compound_string *string)
{
	char	*joined;
	char 	*tmp;
	char 	*to_join;

	env_get(env, "SHELL");
	joined = NULL;
	while (string != NULL)
	{
		to_join = ft_nullcheck(ft_strdup(compound_to_string(env, string)));
		if (joined == NULL)
			joined = to_join;
		else
		{
			tmp = joined;
			joined = ft_strjoin(joined, to_join);
			ft_free(to_join);
			ft_free(tmp);
		}
		string = string->next;
	}
	return (joined);
}

/*
** TODO Refactor to its own file?
*/
static char 		*ft_strjoin3(char *a, char *b, char *c)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*str;

	if (!a || !b || !c)
		return (NULL);
	len1 = ft_strlen(a);
	len2 = ft_strlen(b);
	len3 = ft_strlen(c);
	str = ft_checked_malloc(sizeof(char) * (len1 + len2 + len3 + 1));
	ft_memcpy(str, a, len1 + 1);
	ft_memcpy(str + len1, b, len2 + 1);
	ft_memcpy(str + len1 + len2, c, len3 + 1);
	return (str);
}

static char *test_path(char *path)
{
	struct stat	stat_buffer;
	if (stat(path, &stat_buffer) == 0 && S_ISREG(stat_buffer.st_mode))
		return (path);
	return (NULL);
}

char 		*env_resolve_path_file(t_env *env, char *file)
{
	char		**path;
	char 		*working_dir;
	char		*joined_path;

	if (test_path(file) != NULL)
		return (ft_strdup(file));
	if (file[0] == '.')
	{
		working_dir = getcwd(NULL, 0);
		joined_path = ft_strjoin3(working_dir, "/", file);
		free(working_dir);
		if (test_path(joined_path) != NULL)
			return (joined_path);
		ft_free(joined_path);
	}
	path = ft_split(env_get(env, "PATH"), ':');
	while (*path != NULL)
	{
		joined_path = ft_strjoin3(*path, "/", file);
		if (test_path(joined_path) != NULL)
			return (joined_path);
		ft_free(joined_path);
		path++;
	}
	return (NULL);
}