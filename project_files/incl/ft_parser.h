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
	BEGIN_PARSING,
	PARSING_COMMAND,
	PARSING_IN,
	PARSING_OUT
}						t_parser_ree;

typedef enum			e_redirection_type {
	TRUNCATE,
	APPEND
}						t_redirection_type;

typedef struct			s_redirection_in {
	t_composite_string 	*file;
}						t_redirection_in;

typedef struct			s_redirection_out {
	t_composite_string 	*file;
	t_redirection_type	*type;
}						t_redirection_out;

typedef struct			s_parser_command {
	t_composite_string	*arguments;
	t_redirection_in 	*redirections_in;
	t_redirection_out 	*redirections_out;
}						t_parser_command;

#endif
