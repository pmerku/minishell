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

#include <ft_llist.h>
#include <ft_memory.h>
#include <ft_lex.h>
#include <ft_stdio/ft_printf.h>
#include <ft_libft.h>

/*
 * ree
 */
//static char 	*token_to_str(t_token_type type)
//{
//	if (type == PIPE)
//		return ("PIPE");
//	else if (type == BRACKET_OPEN)
//		return ("BRACKET_OPEN");
//	else if (type == BRACKET_CLOSE)
//		return ("BRACKET_CLOSE");
//	else if (type == STRING)
//		return ("STRING");
//	else if (type == ENV_STRING)
//		return ("ENV_STRING");
//	else if (type == SEMICOLUMN)
//		return ("SEMICOLUMN");
//	else if (type == REDIR_L)
//		return ("REDIR_L");
//	else if (type == REDIR_R)
//		return ("REDIR_R");
//	else if (type == REDIR_RR)
//		return ("REDIR_RR");
//	else if (type == AMPERSAND)
//		return ("AMPERSAND");
//	else if (type == OR)
//		return ("OR");
//	return ("NULL");
//}

//static void		print_token(t_token *token)
//{
//	t_composite_string  *str;
//
//	ft_printf("&a&l * &rToken type &a%s&r\n", token_to_str(token->type));
//	if (token->type == STRING)
//	{
//		str = token->str;
//		while (str != NULL)
//		{
//			ft_printf("    String type &a%s&r: &a%s&r\n",token_to_str(str->type), str->str);
//			str = str->next;
//		}
//	}
//}
/*
 * end ree
 */

static char				composite_string_push(t_composite_string **composite,
		char *str, t_token_type type)
{
	t_composite_string	*last;
	t_composite_string	*new_composite;

	new_composite = ft_malloc(sizeof(t_composite_string));
	if (new_composite == NULL)
		return (0);
	new_composite->str = str;
	new_composite->type = type;
	new_composite->next = NULL;
	if (*composite == NULL)
	{
		*composite = new_composite;
	}
	else
	{
		last = *composite;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new_composite;
	}
	return (1);
}

static char 			lex_next_char(t_lex_state *state)
{
	char c;

	c = state->str[state->offset];
	if (c == '\0')
	{
		return ('\0');
	}
	state->offset++;
	return (c);
}

static char				lex_err(t_lex_state *state, char *err)
{
	*(state->err) = err;
	return (0);
}

static char				peek_next_char(t_lex_state *state)
{
	if (state->str[state->offset] == '\0')
	{
		return ('\0');
	}
	return (state->str[state->offset]);
}

static void 			skip_next_char(t_lex_state *state)
{
	if (state->str[state->offset] == '\0')
		return ;
	state->offset++;
}

static int				is_non_identifier_char(char c)
{
	if (c == ' ' || c == '|' || c == '\'' || c == '"' || c == '>' || c == '<'
		|| c == '&' || c == ';')
		return (0);
	return (1);
}

void					del_comp_string(t_composite_string *str)
{
	t_composite_string *tmp;
	t_composite_string *next;

	next = str;
	while (next != NULL)
	{
		tmp = next->next;
		ft_free(next->str);
		ft_free(next);
		next = tmp;
	}
}

static void				del_elem(void *ptr)
{
	del_comp_string(((t_token *)ptr)->str);
	ft_free(ptr);
}

static char				lex_next_to_char(t_lex_state *state, char *c)
{
	*c = lex_next_char(state);
	return (*c);
}

static char 			create_composite_token(t_lex_state *state,
		t_composite_string *str)
{
	t_token *token;

	token = ft_malloc(sizeof(t_token));
	if (token == NULL)
		return (0);
	token->str = str;
	token->type = STRING;
	if (!ft_llist_push_back(state->tokens, token))
	{
		del_elem(token);
		return (0);
	}
	return (1);
}

static char				create_token(t_lex_state *state, t_token_type type)
{
	t_token *token;

	token = ft_malloc(sizeof(t_token));
	if (token == NULL)
		return (0);
	token->str = NULL;
	token->type = type;
	if (!ft_llist_push_back(state->tokens, token))
	{
		ft_free(token);
		return (0);
	}
	return (1);
}

static char				setup_state(char **err, char *str, t_lex_state *state)
{
	ft_bzero(state, sizeof(t_lex_state));
	state->str = str;
	state->tokens = ft_llist_new(&del_elem);
	state->err = err;
	if (state->tokens == NULL)
	{
		*err = "Failed to create linked list";
		return (0);
	}
	return (1);
}

static int 				is_string_char(char c)
{
	return (c == '\'' || c == '"' || is_non_identifier_char(c));
}

static char 			is_valid_env_var_char(char c, int is_first_char)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	if ((c >= '0' && c <= '9') && is_first_char == 0)
		return (1);
	return (0);
}

static char				*escape_chars(char str_type, char *str)
{
	size_t idx;
	size_t cur;

	idx = 0;
	cur = 0;
	if (str_type == '\'')
		return (str);
	while (str[cur] != '\0')
	{
		if (str[cur] == '\\')
		{
			if (str_type == '"' && (str[cur + 1] == '$' || str[cur + 1] == '`' || str[cur + 1] == '"'))
				cur++;
			else if (str_type == '\0')
				cur++;
		}
		str[idx] = str[cur];
		idx++;
		cur++;
	}
	str[idx] = '\0';
	return (str);
}

static char				push_substr(t_lex_state *state, size_t start,
		size_t end, t_token_type str_type)
{
	char	*substr;

	substr = ft_substr(state->str, start, end - start);
	if (substr == NULL)
		return (lex_err(state, "Failed to allocate substring"));
	if (!composite_string_push(&state->current_string, substr, str_type))
	{
		ft_free(substr);
		return (lex_err(state, "Failed to push string to composite string"));
	}
	return (1);
}

static char				push_escaped_substr(t_lex_state *state, size_t start,
		size_t end, char type)
{
	char *substr;

	substr = ft_substr(state->str, start, end - start);
	if (substr == NULL)
		return (lex_err(state, "Failed to allocate substring"));
	substr = escape_chars(type, substr);
	if (!composite_string_push(&state->current_string, substr, STRING))
	{
		ft_free(substr);
		return (lex_err(state, "Failed to push string to composite string"));
	}
	return (1);
}

static char				read_env_var(t_lex_state *state)
{
	size_t	start;
	char 	c;
	char 	is_bracket;

	is_bracket = peek_next_char(state) == '{' ? 1 : 0;
	state->offset += is_bracket;
	start = state->offset;
	while (lex_next_to_char(state, &c) != '\0')
	{
		if ((is_bracket && c == '}')
			|| !is_valid_env_var_char(c, state->offset == start + 1))
			break ;
	}
	if (!push_substr(state, start, state->offset, ENV_STRING))
		return (0);
	state->offset += is_bracket;
	return (1);
}

static char 			export_prev_str(t_lex_state *state, char str_type,
		size_t *start)
{
	if (*start != state->offset - 1)
	{
		if (!push_escaped_substr(state, *start, state->offset - 1,
				str_type))
			return (0);
	}
	if (!read_env_var(state))
		return (0);
	*start = state->offset;
	return (1);
}

static char				read_quoted_str(t_lex_state *state)
{
	size_t	start;
	char	c;

	start = state->offset;
	while (lex_next_to_char(state, &c) != '\0')
	{
		if (c == '\\')
		{
			if (peek_next_char(state) == '\0')
				break;
			if (peek_next_char(state) == '"')
			{
				skip_next_char(state);
				continue ;
			}
		}
		if (c == '$' && !export_prev_str(state, '"', &start))
			return (0);
		if (c == '"')
			break ;
	}
	if (c != '"')
		return (lex_err(state, "Unterminated quoted string"));
	if (start != state->offset - 1)
		return (push_escaped_substr(state, start, state->offset - 1,
				'"'));
	return (1);
}

static char				read_raw_str(t_lex_state *state)
{
	size_t	start;
	char	c;

	start = state->offset;
	while (lex_next_to_char(state, &c) != '\0' && c != ' ')
	{
		if (!is_non_identifier_char(c))
			break ;
		if (c == '\\')
		{
			if (peek_next_char(state) == '\0')
				break;
			skip_next_char(state);
		}
		if (c == '$')
			if (!export_prev_str(state, '\0', &start))
				return (0);
	}
	if (start < state->offset)
	{
		if (c != '\0' && peek_next_char(state) != '\0')
			state->offset--;
		return (push_escaped_substr(state, start, state->offset, '\0'));
	}
	return (1);
}

static char				read_literal_str(t_lex_state *state)
{
	size_t	start;
	size_t	end;
	char	c;

	start = state->offset;
	while (lex_next_to_char(state, &c) != '\0' && c != '\'') ;
	if (c != '\'')
		return (lex_err(state, "Unterminated literal string"));
	end = state->offset;
	if (c == '\'')
		end--;
	if (start == end)
		return (1);
	return (push_substr(state, start, end, STRING));
}

static char				finish_str_token(t_lex_state *state)
{
	char success;

	if (state->current_string != NULL)
	{
		success = create_composite_token(state, state->current_string);
		state->current_string = NULL;
		return (success);
	}
	return (1);
}

static char 			lex_str(t_lex_state *state, char type)
{
	char success;

	if (type != '\'' && type != '"' && is_non_identifier_char(type))
		state->offset--;
	if (type == '\'')
		success = read_literal_str(state);
	else if (type == '"')
		success = read_quoted_str(state);
	else
		success = read_raw_str(state);
	return (success);
}

static char				lex_other(t_lex_state *state, char c)
{
	if (c == '|' && peek_next_char(state) == '|')
	{
		skip_next_char(state);
		return (create_token(state, OR));
	}
	else if (c == '|')
		return (create_token(state, PIPE));
	else if (c == '<')
		return (create_token(state, REDIR_L));
	else if (c == '>' && peek_next_char(state) == '>')
	{
		skip_next_char(state);
		return (create_token(state, REDIR_RR));
	}
	else if (c == '>')
		return (create_token(state, REDIR_R));
	else if (c == '&')
		return (create_token(state, AMPERSAND));
	else if (c == '(')
		return (create_token(state, BRACKET_OPEN));
	else if (c == ')')
		return (create_token(state, BRACKET_CLOSE));
	else if (c == ';')
		return (create_token(state, SEMICOLUMN));
	return (1);
}

static char				lex_loop(t_lex_state *state)
{
	char c;

	while (lex_next_to_char(state, &c) != '\0')
	{
		if (is_string_char(c))
		{
			if (!lex_str(state, c))
				return (0);
		}
		else
		{
			if (!finish_str_token(state))
				return (0);
			if (!lex_other(state, c))
				return (0);
		}
	}
	if (!finish_str_token(state))
		return (0);
	return (1);
}

t_llist					*lex(char *str, char **err)
{
	t_lex_state	state;

	if (!setup_state(err, str, &state))
		return (NULL);
	if (!lex_loop(&state))
	{
		ft_llist_free(&state.tokens);
		return (NULL);
	}
//	ft_llist_iter(state.tokens, (void (*)(void *))&print_token);
	return (state.tokens);
}
