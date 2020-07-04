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
# include <sys/types.h>

# define STANDARD_IN	0
# define STANDARD_OUT	1
# define PIPE_IN		0
# define PIPE_OUT		1

# define COMMAND_NOT_FOUND	127
# define SIGNAL_TERMINATED	128

typedef struct	s_executor {
	char	**args;
	int		tmp_in;
	int		tmp_out;
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	int		fd_pipe[2];
	int		status;
}				t_executor;

int				execute(t_parser_command ***commands, t_env *env);
int				get_input(t_parser_command *command, t_executor *exec,
				t_env *env, int prev_fd);
int				get_output(t_parser_command *command, t_executor *exec,
				t_env *env, int last_command);
int				exec_fork(t_executor *exec, char **args, t_env *env);
int				exit_helper(char **args, t_executor *exec);
char			**parse_args(t_parser_command *command, t_env *env);
int 			exec_num_commands(t_parser_command ***commands);


#endif
