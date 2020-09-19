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

#ifndef FT_ENV_H
# define FT_ENV_H

# include <ft_lex.h>

typedef struct	s_env {
	char	**vars;
	int		last_status;
}				t_env;

t_env			*env_from(char **envp);
void			env_set(t_env *env, char *key, char *value);
void			env_remove(t_env *env, char *key);

/*
** DO NOT FREE THE ENV VAR RETURNED FROM THIS METHOD
*/
char			*env_get(t_env *env, char *key);

char			*env_parse_string(t_env *env, t_composite_string *string);
char			*env_resolve_path_file(t_env *env, char *binary);

#endif
