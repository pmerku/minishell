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

#ifndef FT_EXEC_H
# define FT_EXEC_H

#include <ft_env.h>
#include <ft_parser.h>
#include <ft_lex.h>

typedef struct	s_simple_command
{
	char		**args;
	char 		*infile;
	char 		*outfile;
	int 		background;
}				t_simple_command;

int		execute(t_parser_command ***commands, t_env *env);

int		exec_cd(char **args);
int 	exec_exit(char **args);
int 	exec_echo(char **args);

#endif
