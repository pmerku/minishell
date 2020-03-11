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

#ifndef FT_LEX_H
# define FT_LEX_H

# include <stddef.h>
# include <ft_llist.h>

/*
** Represents the type of a token
**
** PIPE				|
** BRACKET_OPEN		(
** BRACKET_CLOSE	)
** STRING			A string literal
** ENV_STRING		A string representing the key of an environmental variable
** SEMICOLUMN		;
** REDIR_L			<
** REDIR_LL			<<
 * REDIR_R			>
 * REDIR_RR			>>
 * AMPERSAND		&
 * AND				&&
 * OR				||
*/
typedef enum			e_token_type {
	PIPE,
	BRACKET_OPEN,
	BRACKET_CLOSE,
	STRING,
	ENV_STRING,
	SEMICOLUMN,
	REDIR_L,
	REDIR_LL,
	REDIR_R,
	REDIR_RR,
	AMPERSAND,
	AND,
	OR
}						t_token_type;

/*
** A composite string is a fancy linked list with string elements to support
** composite strings just like Bash does.
**
** The following is a valid string in Bash, and will be evaluated to one
** string. Consider environmental variable 'EC' to be 'ec'
** $EC"h"'o' -> echo
**
** Each "sub" string has to be evaluated individually.
*/
typedef struct			t_composite_string {
	t_token_type 				type;
	char 						*str;
	struct t_composite_string	*next;
}						t_composite_string;

typedef struct			s_token {
	t_token_type		type;
	t_composite_string	*str;
}						t_token;

typedef struct			s_lex_state {
	char				*str;
	size_t				offset;
}						t_lex_state;

t_llist					*lex(char *str);

#endif