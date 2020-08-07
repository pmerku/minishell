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

# include <ft_env.h>
# include <ft_parser.h>
# include <ft_lex.h>
# include <sys/types.h>

# define STANDARD_IN	0
# define STANDARD_OUT	1
# define PIPE_IN		0
# define PIPE_OUT		1

# define COMMAND_NOT_FOUND	127
# define SIGNAL_TERMINATED	128

typedef struct	s_executor {
	int 	tmp_in;
	int 	tmp_out;
	int 	fd_in;
	int 	fd_out;
	pid_t	pid;
	int 	pipe_prev[2];
	int 	pipe_next[2];
	int 	status;
}				t_executor;

int				execute(t_parser_command ***commands, t_env *env);

#endif
