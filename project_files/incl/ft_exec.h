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

# define EXECVE_ERROR		126
# define COMMAND_NOT_FOUND	127
# define SIGNAL_TERMINATED	128

typedef struct	s_executor {
	int			built_in:1;
	int			fd_in;
	int			fd_out;
	int			fd_tmp_in;
	int			fd_tmp_out;
	pid_t		pid;
	int			pipe_prev[2];
	int			pipe_next[2];
	int			last_pid;
	int			status;
	struct stat	buf;
	char		*path;
	size_t		i;
	char		**args;
}				t_executor;

int				execute(t_parser_command ***commands, t_env *env);
void			f_signal_handler_exec(int signo);
void			f_signal_init_exec(void);
int				get_in_fd(t_parser_command *command, t_env *env);
int				get_out_fd(t_parser_command *command, t_env *env);
int				builtin_search(char **args, t_executor *exec, t_env *env,
				t_parser_command *list);
int				f_builtin_search(char **args, t_env *env);
int				exec_fork(char **args, t_executor *exec, t_env *env,
				t_parser_command *list);
void			init_pipes(t_executor *exec);
int				close_pipes(char **args, t_executor *exec);
int				make_pipes(t_executor *exec, t_parser_command **list,
				t_parser_command *command, t_env *env);
void			exit_codes(t_executor *exec, t_env *env);

#endif
