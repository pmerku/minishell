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

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct	s_shell {
	t_env				*env;
	char				*line;
	int					gnl_ret;
	t_llist				*lex_tokens;
	t_parser_command	***parse_tokens;
	char				*dir;
	char				*err;
}				t_shell;

void			cleanup(t_shell *shell);
void			signal_init(void);
void			signal_handler(int signo);

#endif
