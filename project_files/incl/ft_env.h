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

#ifndef FT_ENV_H
# define FT_ENV_H

# include <ft_lex.h>

typedef struct		s_env {
	char			**vars;
}					t_env;

t_env				*env_from(char **envp);
void				env_set(t_env *env, char *key, char *value);
void				env_remove(t_env *env, char *key);

/*
** DO NOT FREE THE ENV VAR RETURNED FROM THIS METHOD
*/
char 				*env_get(t_env *env, char *key);

char				*env_parse_string(t_env *env, t_composite_string *string);
void				env_print_all(t_env *env);
char 				*env_resolve_path_file(t_env *env, char *binary);

#endif
