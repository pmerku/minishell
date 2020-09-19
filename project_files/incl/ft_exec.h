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

#ifndef FT_EXEC_H
# define FT_EXEC_H

# include <ft_env.h>
# include <ft_parser.h>
# include <ft_lex.h>
# include <sys/types.h>
# include <sys/stat.h>

# define STANDARD_IN	0
# define STANDARD_OUT	1
# define PIPE_IN		0
# define PIPE_OUT		1

# define COMMAND_NOT_FOUND	127
# define SIGNAL_TERMINATED	128

typedef struct	s_executor {
	int			built_in:1;
	int 		fd_in;
	int 		fd_out;
	int 		fd_tmp_in;
	int 		fd_tmp_out;
	pid_t		pid;
	int 		pipe_prev[2];
	int 		pipe_next[2];
	int			last_pid;
	int 		status;
	struct stat	buf;
}				t_executor;

int				execute(t_parser_command ***commands, t_env *env);

#endif
