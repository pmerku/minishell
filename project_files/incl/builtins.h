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

#ifndef BUILTINS_H
# define BUILTINS_H

# include <ft_env.h>

typedef int		t_builtin_func(char **args, t_env *env);

typedef struct		s_builtin_list
{
	char			*name;
	t_builtin_func	*func;
}					t_builtin_list;

int				builtin_echo(char **args, t_env *env);
int				builtin_cd(char **args, t_env *env);
int				builtin_pwd(char **args, t_env *env);
int				builtin_export(char **args, t_env *env);
int				builtin_unset(char **args, t_env *env);
int				builtin_env(char **args, t_env *env);
int				builtin_exit(char **args, t_env *env);

#endif
