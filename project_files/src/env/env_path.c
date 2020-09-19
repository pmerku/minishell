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
#include <ft_libft.h>
#include <ft_memory.h>
#include <zconf.h>
#include <stdlib.h>
#include <sys/stat.h>

static char *test_path(char *path)
{
	struct stat	stat_buffer;
	if (stat(path, &stat_buffer) == 0 && S_ISREG(stat_buffer.st_mode))
		return (path);
	return (NULL);
}

static char	*path_join(char *joined_path, t_env *env, char *file)
{
	size_t	i;
	char	**path;

	i = 0;
	path = ft_split(env_get(env, "PATH"), ':');
	while (path[i])
	{
		joined_path = ft_strjoin3(path[i], "/", file);
		if (test_path(joined_path) != NULL) {
			ft_free_array(path);
			return (joined_path);
		}
		ft_free(joined_path);
		i++;
	}
	ft_free_array(path);
	return (NULL);
}

char 		*env_resolve_path_file(t_env *env, char *file)
{
	char 		*working_dir;
	char		*joined_path;

	joined_path = NULL;
	if ((file[0] == '.' || file[0] == '/') && test_path(file) != NULL)
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
	return (path_join(joined_path, env, file));
}
