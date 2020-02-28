/* ************************************************************************** */
/*                                                                            */
/*   Project: project_files                               ::::::::            */
/*   Members: dvoort, prmerku                           :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include <stddef.h>
# include <linked_list.h>

/*
** Represents the type of a token
**
** PIPE				|
** BRACKET_OPEN		(
** BRACKET_CLOSE	)
** STRING			A string where environmental variables get parsed
** STRING_LITERAL	A string where environmental variables don't get parsed
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
	STRING_LITERAL,
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
** A compound string is a fancy linked list with string elements to support
** compound strings just like Bash does.
**
** The following is a valid string in Bash, and will be evaluated to one
** string. Consider environmental variable 'EC' to be 'ec'
** $EC"h"'o' -> echo
**
** Each "sub" string has to be evaluated individually.
*/
typedef struct			s_compound_string {
	t_token_type 				type;
	char 						*str;
	struct s_compound_string	*next;
}						t_compound_string;

typedef struct			s_token {
	t_token_type		type;
	t_compound_string	*str;
}						t_token;

typedef struct			s_lex_state {
	char				*str;
	size_t				offset;
}						t_lex_state;

t_linked_list			*lex(char *str);

#endif