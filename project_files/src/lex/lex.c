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

#include <ft_lex.h>
#include <ft_stdio/ft_printf.h>
#include <ft_libft.h>
#include <ft_memory.h>
#include <ft_llist.h>

static void		composite_string_push(t_composite_string **composite, char *str, t_token_type type)
{
	t_composite_string	*last;
	t_composite_string	*new_composite;

	new_composite = ft_checked_malloc(sizeof(t_composite_string));
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
}

static char 	lex_next_char(t_lex_state *state)
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

static char		peek_current_char(t_lex_state *state)
{
	if (state->str[state->offset] == '\0')
	{
		return ('\0');
	}
	return (state->str[state->offset]);
}

static void 	skip_next_char(t_lex_state *state)
{
	if (state->str[state->offset] == '\0')
		return ;
	state->offset++;
}

static char		is_non_identifier_char(char c)
{
	if (c == ' ' || c == '|' || c == '\'' || c == '"' || c == '>' || c == '<' || c == '&' || c == ';')
		return (0);
	return (1);
}

static char		*escape_chars(char str_type, char *str)
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

/*
** Reads a string surrounded with '. Need to come up with a better name
*/
static void		read_literal_string(t_composite_string **str, t_lex_state *state)
{
	size_t	start;
	size_t	end;
	char	c;

	start = state->offset;
	while ((c = lex_next_char(state)) != '\0' && c != '\'') ;
	if (c != '\'')
		ft_printf("&cTODO - Handle unterminated string\n");
	end = state->offset;
	if (c == '\'')
		end--;
	composite_string_push(str, ft_substr(state->str, start, end - start), STRING);
}

static char 	is_valid_env_var_char(char c, int is_first_char)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	if ((c >= '0' && c <= '9') && is_first_char == 0)
		return (1);
	return (0);
}


static void		read_env_var(t_composite_string **str, t_lex_state *state)
{
	size_t	start;
	char 	c;
	char 	is_bracket;

	is_bracket = peek_current_char(state) == '{' ? 1 : 0;
	state->offset += is_bracket;
	start = state->offset;
	while ((c = peek_current_char(state)) != '\0')
	{
		if (is_bracket && c == '}')
			break ;
		else if (!is_valid_env_var_char(c, state->offset == start + 1))
			break ;
		skip_next_char(state);
	}
	composite_string_push(str, ft_substr(state->str, start, state->offset - start), ENV_STRING);
	state->offset += is_bracket;
}

/*
** Reads a string surrounded by nothing. Need to come up with a better name
*/
static void		read_raw_str(t_composite_string **str, t_lex_state *state)
{
	size_t	start;
	size_t	end;
	char	c;

	start = state->offset;
	while ((c = lex_next_char(state)) != '\0' && c != ' ')
	{
		if (!is_non_identifier_char(c))
			break ;
		if (c == '\\')
		{
			if (peek_current_char(state) == '\0')
				break;
			skip_next_char(state);
		}
		if (c == '$')
		{
			if (start != state->offset - 1)
				composite_string_push(str, escape_chars('\0', ft_substr(state->str, start, state->offset - start - 1)), STRING);
			read_env_var(str, state);
			start = state->offset;
			if (!is_non_identifier_char(peek_current_char(state)))
				return ;
		}
	}
	if (start != state->offset - 1)
	{
		if (c != '\0' && peek_current_char(state) != '\0')
			state->offset--;
		end = state->offset;
		composite_string_push(str, escape_chars('\0',ft_substr(state->str, start,end - start)), STRING);
	}
}

/*
** Reads a string surrounded by double quotes. Need to come up with a better name
*/
static void		read_quoted_str(t_composite_string **str, t_lex_state *state)
{
	size_t	start;
	size_t	end;
	char	c;

	start = state->offset;
	while ((c = lex_next_char(state)) != '\0')
	{
		if (c == '\\')
		{
			if (peek_current_char(state) == '\0')
				break;
			if (peek_current_char(state) == '"')
			{
				skip_next_char(state);
				continue ;
			}
		}
		if (c == '$')
		{
			if (start != state->offset - 1)
				composite_string_push(str, escape_chars('\0', ft_substr(state->str, start, state->offset - start - 1)), STRING);
			read_env_var(str, state);
			start = state->offset;
		}
		if (c == '"')
			break ;
	}
	if (start != state->offset - 1)
	{
		if (c != '"')
			ft_printf("&cTODO - Handle unterminated string: %c\n", c);
		end = state->offset;
		if (c == '"')
			end--;
		composite_string_push(str, escape_chars('\0',ft_substr(state->str, start,end - start)), STRING);
	}
}

static void		del_elem(void *ptr)
{
	t_token				*token;
	t_composite_string	*tmp;
	t_composite_string	*next;

	token = ptr;
	next = token->str;
	while (next != NULL)
	{
		tmp = next->next;
		ft_free(next->str);
		ft_free(next);
		next = tmp;
	}
	ft_free(ptr);
}

static t_token	*create_token(t_token_type type)
{
	t_token *token;

	token = ft_checked_malloc(sizeof(t_token));
	token->str = NULL;
	token->type = type;
	return (token);
}

static t_token	*create_composite_token(t_composite_string *str)
{
	t_token *token;

	token = ft_checked_malloc(sizeof(t_token));
	token->str = str;
	token->type = STRING;
	return (token);
}

static char 	*token_to_str(t_token_type type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == BRACKET_OPEN)
		return ("BRACKET_OPEN");
	else if (type == BRACKET_CLOSE)
		return ("BRACKET_CLOSE");
	else if (type == STRING)
		return ("STRING");
	else if (type == ENV_STRING)
		return ("ENV_STRING");
	else if (type == SEMICOLUMN)
		return ("SEMICOLUMN");
	else if (type == REDIR_L)
		return ("REDIR_L");
	else if (type == REDIR_LL)
		return ("REDIR_LL");
	else if (type == REDIR_R)
		return ("REDIR_R");
	else if (type == REDIR_RR)
		return ("REDIR_RR");
	else if (type == AMPERSAND)
		return ("AMPERSAND");
	else if (type == AND)
		return ("AND");
	else if (type == OR)
		return ("OR");
	return ("NULL");
}

static void		print_token(t_token *token)
{
	t_composite_string  *str;

	ft_printf("&a&l * &rToken type &a%s&r\n", token_to_str(token->type));
	if (token->type == STRING)
	{
		str = token->str;
		while (str != NULL)
		{
			ft_printf("    String type &a%s&r: &a%s&r\n",token_to_str(str->type), str->str);
			str = str->next;
		}
	}
}

t_llist			*lex(char *str)
{
	t_lex_state			state;
	t_llist				*lst;
	t_composite_string	*current_string;
	char				c;

	ft_bzero(&state, sizeof(t_lex_state));
	state.str = str;
	current_string = NULL;
	lst = ft_llist_new(&del_elem);
	while ((c = lex_next_char(&state)) != '\0') {
		if (c == '\'')
		{
			read_literal_string(&current_string, &state);
		}
		else if (c == '"')
		{
			read_quoted_str(&current_string, &state);
		}
		else if (is_non_identifier_char(c))
		{
			state.offset--;
			read_raw_str(&current_string, &state);
		}
		else
		{
			if (current_string != NULL)
			{
				ft_llist_push_back(lst, create_composite_token(current_string));
				current_string = NULL;
			}
			if (c == '|') {
				if (peek_current_char(&state) == '|') {
					skip_next_char(&state);
					ft_llist_push_back(lst, create_token(OR));
				} else {
					ft_llist_push_back(lst, create_token(PIPE));
				}
			}
			else if (c == '<') {
				if (peek_current_char(&state) == '<') {
					skip_next_char(&state);
					ft_llist_push_back(lst, create_token(REDIR_LL));
				} else {
					ft_llist_push_back(lst, create_token(REDIR_L));
				}
			}
			else if (c == '>') {
				if (peek_current_char(&state) == '>') {
					skip_next_char(&state);
					ft_llist_push_back(lst, create_token(REDIR_RR));
				} else {
					ft_llist_push_back(lst, create_token(REDIR_R));
				}
			}
			else if (c == '&')
			{
				if (peek_current_char(&state) == '&') {
					skip_next_char(&state);
					ft_llist_push_back(lst, create_token(AND));
				} else {
					ft_llist_push_back(lst, create_token(AMPERSAND));
				}
			}
			else if (c == '(')
			{
				ft_llist_push_back(lst, create_token(BRACKET_OPEN));
			}
			else if (c == ')')
			{
				ft_llist_push_back(lst, create_token(BRACKET_CLOSE));
			}
			else if (c == ';')
			{
				ft_llist_push_back(lst, create_token(SEMICOLUMN));
			}
		}
	}
	if (current_string != NULL)
	{
		ft_llist_push_back(lst, create_composite_token(current_string));
		current_string = NULL;
	}

	ft_printf("&e&lLexical Analysis result:&r\n");
	ft_llist_iter(lst, (void (*)(void *))&print_token);
	return (lst);
}
