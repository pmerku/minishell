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
#include <sys/types.h>

typedef struct	s_simple_command
{
//	char				**args;
	char 				*infile;
	char 				*outfile;
	t_redirection_type	type;
}				t_simple_command;

typedef struct	s_executor {
	int 	tmp_in;
	int 	tmp_out;
	int 	fd_in;
	int 	fd_out;
	pid_t	pid;
	int 	fd_pipe[2];
	int 	status;
}				t_executor;

int				execute(t_parser_command ***commands, t_env *env);

#endif
