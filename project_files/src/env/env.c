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

void		env_print_all(t_env *env)
{
	char **split;
	char **list;

	list = env->vars;
	ft_printf("&b&l&n%-20s &f= &b&l%-50s&r\n", "Key", "Value");
	while (*list != NULL)
	{
		split = ft_nsplit(*list, '=', 2);
		ft_printf("&b%-20s &r= %s\n", split[0], split[1] == NULL ? "" : split[1]);
		ft_strarr_free(split);
		list++;
	}
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
	char 	removed;

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

char 		*env_get(t_env *env, char *key)
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
	size_t 		i;

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
	i = 0;
	path = ft_split(env_get(env, "PATH"), ':');
	while (path[i])
	{
		joined_path = ft_strjoin3(path[i], "/", file);
		if (test_path(joined_path) != NULL) {
			ft_strarr_free(path);
			return (joined_path);
		}
		ft_free(joined_path);
		i++;
	}
	ft_strarr_free(path);
	return (NULL);
}