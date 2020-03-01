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

#ifndef FT_ENV_H
# define FT_ENV_H

# include <lex.h>

typedef struct		s_env {
	struct s_env	*next;
	char 			*key;
	char 			*value;
}					t_env;

t_env				*env_from(char **envp);
void				env_set(t_env **env, char *key, char *value);
void				*env_remove(t_env **env, char *key);
char 				*env_get(t_env *env, char *key);
char				*env_parse_string(t_env *env, t_compound_string *string);
void				env_print_all(t_env *env);

#endif
