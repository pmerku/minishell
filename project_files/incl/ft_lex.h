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
** REDIR_R			>
** REDIR_RR			>>
** AMPERSAND		&
** OR				||
*/
typedef enum			e_token_type {
	PIPE,
	BRACKET_OPEN,
	BRACKET_CLOSE,
	STRING,
	ENV_STRING,
	SEMICOLUMN,
	REDIR_L,
	REDIR_R,
	REDIR_RR,
	AMPERSAND,
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
typedef struct			s_composite_string {
	t_token_type				type;
	char						*str;
	struct t_composite_string	*next;
}						t_composite_string;

typedef struct			s_token {
	t_token_type		type;
	t_composite_string	*str;
}						t_token;

typedef struct			s_lex_state {
	char				*str;
	char				**err;
	size_t				offset;
	t_composite_string	*current_string;
	t_llist				*tokens;
}						t_lex_state;

t_llist					*lex(char *str, char **err);
void					del_comp_string(t_composite_string *str);

char					composite_string_push(t_composite_string **composite,
						char *str, t_token_type type);
char					lex_next_char(t_lex_state *state);
char					lex_err(t_lex_state *state, char *err);
char					peek_next_char(t_lex_state *state);
void					skip_next_char(t_lex_state *state);
int						is_non_identifier_char(char c);
void					del_elem(void *ptr);
char					lex_next_to_char(t_lex_state *state, char *c);
char					create_composite_token(t_lex_state *state,
						t_composite_string *str);
char					create_token(t_lex_state *state, t_token_type type);
char					setup_state(char **err, char *str, t_lex_state *state);
int						is_string_char(char c);
char					is_valid_env_var_char(char c, int is_first_char);
char					*escape_chars(char str_type, char *str);
char					push_substr(t_lex_state *state, size_t start,
						size_t end, t_token_type str_type);
char					push_escaped_substr(t_lex_state *state, size_t start,
						size_t end, char type);
char					read_env_var(t_lex_state *state);
char					export_prev_str(t_lex_state *state, char str_type,
						size_t *start);
char					read_quoted_str(t_lex_state *state);
char					read_raw_str(t_lex_state *state);
char					read_literal_str(t_lex_state *state);
char					finish_str_token(t_lex_state *state);
char					lex_str(t_lex_state *state, char type);
char					lex_other(t_lex_state *state, char c);
char					lex_loop(t_lex_state *state);

#endif
