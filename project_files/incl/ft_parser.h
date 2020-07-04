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

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include <ft_lex.h>

typedef enum			e_parser_ree {
	PARSING_COMMAND,
	PARSING_FILENAME,
	EXPECTING_TOKEN
}						t_parser_ree;

typedef enum			e_redirection_type {
	IN,
	TRUNCATE,
	APPEND
}						t_redirection_type;

typedef struct			s_redirection {
	t_composite_string	*file;
	t_redirection_type	type;
}						t_redirection;

typedef struct			s_parser_command {
	t_composite_string	**arguments;
	t_redirection		**redirections_in;
	t_redirection		**redirections_out;
}						t_parser_command;

typedef struct			s_parser_state {
	t_parser_ree		state;
	t_token				*previous_token;
	t_token				*current_token;
	t_parser_command	*current_command;
	t_parser_command	***commands;
}						t_parser_state;

/*
** Returns a list with parser commands in a two-dimensional array. Each array
** has to be evaluated separately, but each command in its array should be piped
** in the order that the commands appear in the array.
**
** Each array is NULL-terminated.
**
** The command `echo hello | cat -e; yes`
**
** Will result in the following: [["echo hello", "cat -e"], ["yes"]]. Here,
** `echo hello` should be piped into `cat -e`, and `yes` should be evaluated
** separately.
*/
t_parser_command		***parse(t_llist *tokens, char **err);
void					free_parse_results(t_parser_command ***commands);

#endif
