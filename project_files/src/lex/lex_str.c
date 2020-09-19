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

#include <ft_memory.h>
#include <ft_lex.h>

char			read_raw_str(t_lex_state *state)
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
				break ;
			skip_next_char(state);
		}
		if (c == '$')
			if (!export_prev_str(state, '\0', &start))
				return (0);
	}
	if (start < state->offset)
	{
		if ((c != '\0' && peek_next_char(state) != '\0') || c == ' ')
			state->offset--;
		return (push_escaped_substr(state, start, state->offset, '\0'));
	}
	return (1);
}

char			read_literal_str(t_lex_state *state)
{
	size_t	start;
	size_t	end;
	char	c;

	start = state->offset;
	while (lex_next_to_char(state, &c) != '\0' && c != '\'')
		;
	if (c != '\'')
		return (lex_err(state, "Unterminated literal string"));
	end = state->offset;
	if (c == '\'')
		end--;
	if (start == end)
		return (1);
	return (push_substr(state, start, end, STRING));
}

char			finish_str_token(t_lex_state *state)
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

char			lex_str(t_lex_state *state, char type)
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
