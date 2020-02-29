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

#include <lex.h>
#include <printf.h>
#include <libft.h>
#include <memmgmt.h>
#include <linked_list.h>

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
	ft_printf("escape chars: %s\n", str);
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

static char 	*read_str(t_lex_state *state, char str_type)
{
	size_t	start;
	size_t	end;
	char	c;
	char	next;

	start = state->offset;
	while ((c = lex_next_char(state)) != '\0'){
		if (str_type == '\0' && !is_non_identifier_char(c) && c != str_type)
			break ;
		if (c == '\\' && str_type != '\'')
		{
			next = peek_current_char(state);
			if (next == '\0')
				break ;
			if ((str_type == '"' && next == '"'))
			{
				skip_next_char(state);
				continue;
			}
			else if (str_type == '\0')
			{
				skip_next_char(state);
				continue ;
			}
		}
		if (c == str_type)
			break ;
	}
	if (str_type == '\0' && c != '\0' && peek_current_char(state) != '\0')
		state->offset--;
	end = state->offset;
	if ((str_type != '\0' && c == str_type))
		end--;
	return (escape_chars(str_type, ft_substr(state->str, start, end - start)));
}

static void		del_elem(void *ptr)
{
	ft_printf("Delete %p\n", ptr);
}

static t_token	*create_token(t_token_type type)
{
	t_token *token;

	token = ft_checked_malloc(sizeof(t_token));
	token->str = NULL;
	token->type = type;
	return (token);
}

static t_token	*create_compound_token(t_compound_string *str)
{
	t_token *token;

	token = ft_checked_malloc(sizeof(t_token));
	token->str = str;
	token->type = STRING;
	return (token);
}

static void		compound_string_push(t_compound_string **compound, char *str, t_token_type type)
{
	t_compound_string	*last;
	t_compound_string	*new_compound;

	new_compound = ft_checked_malloc(sizeof(t_compound_string));
	new_compound->str = str;
	new_compound->type = type;
	new_compound->next = NULL;
	if (*compound == NULL)
	{
		*compound = new_compound;
	}
	else
	{
		last = *compound;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new_compound;
	}
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
	else if (type == STRING_LITERAL)
		return ("STRING_LITERAL");
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
	t_compound_string  *str;

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

t_linked_list	*lex(char *str)
{
	t_lex_state			state;
	t_linked_list		*lst;
	t_compound_string	*current_string;
	char				c;

	ft_bzero(&state, sizeof(t_lex_state));
	state.str = str;
	current_string = NULL;
	lst = linked_list_new(&del_elem);
	while ((c = lex_next_char(&state)) != '\0') {
		if (c == '|') {
			if (peek_current_char(&state) == '|') {
				skip_next_char(&state);
				linked_list_push_back(lst, create_token(OR));
			} else {
				linked_list_push_back(lst, create_token(PIPE));
			}
		}
		else if (c == '<') {
			if (peek_current_char(&state) == '<') {
				skip_next_char(&state);
				linked_list_push_back(lst, create_token(REDIR_LL));
			} else {
				linked_list_push_back(lst, create_token(REDIR_L));
			}
		}
		else if (c == '>') {
			if (peek_current_char(&state) == '>') {
				skip_next_char(&state);
				linked_list_push_back(lst, create_token(REDIR_RR));
			} else {
				linked_list_push_back(lst, create_token(REDIR_R));
			}
		}
		else if (c == '&')
		{
			if (peek_current_char(&state) == '&') {
				skip_next_char(&state);
				linked_list_push_back(lst, create_token(AND));
			} else {
				linked_list_push_back(lst, create_token(AMPERSAND));
			}
		}
		else if (c == '(')
		{
			linked_list_push_back(lst, create_token(BRACKET_OPEN));
		}
		else if (c == ')')
		{
			linked_list_push_back(lst, create_token(BRACKET_CLOSE));
		}
		else if (c == ';')
		{
			linked_list_push_back(lst, create_token(SEMICOLUMN));
		}
		else if (c == '\'')
		{
			compound_string_push(&current_string, read_str(&state, '\''), STRING_LITERAL);
		}
		else if (c == '"')
		{
			compound_string_push(&current_string, read_str(&state, '"'), STRING);
		}
		else if (is_non_identifier_char(c))
		{
			state.offset--;
			compound_string_push(&current_string, read_str(&state, '\0'), STRING);
		}
		else if (c == ' ' && current_string != NULL)
		{
			linked_list_push_back(lst, create_compound_token(current_string));
			current_string = NULL;
		}
	}
	if (current_string != NULL)
	{
		linked_list_push_back(lst, create_compound_token(current_string));
		current_string = NULL;
	}

	ft_printf("&e&lLexical Analysis result:&r\n");
	linked_list_iter(lst, (void (*)(void *))&print_token);
	return (lst);
}