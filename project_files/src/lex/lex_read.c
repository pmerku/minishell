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

char		read_env_var(t_lex_state *state)
{
	size_t	start;
	char	c;
	char	is_bracket;

	is_bracket = peek_next_char(state) == '{' ? 1 : 0;
	state->offset += is_bracket;
	start = state->offset;
	while (lex_next_to_char(state, &c) != '\0')
	{
		if (is_bracket && c == '}')
			break ;
		if (!is_valid_env_var_char(c, state->offset == start + 1))
		{
			if (state->offset != start + 1)
				state->offset--;
			break ;
		}
	}
	if (!push_substr(state, start, state->offset - is_bracket, ENV_STRING))
		return (0);
	state->offset += is_bracket;
	return (1);
}

char		export_prev_str(t_lex_state *state, char str_type, size_t *start)
{
	if (*start != state->offset - 1)
	{
		if (!push_escaped_substr(state, *start, state->offset - 1, str_type))
			return (0);
	}
	if (!read_env_var(state))
		return (0);
	*start = state->offset;
	return (1);
}

char		read_quoted_str(t_lex_state *state)
{
	size_t	start;
	char	c;

	start = state->offset;
	while (lex_next_to_char(state, &c) != '\0')
	{
		if (c == '\\')
		{
			if (peek_next_char(state) == '\0')
				break ;
			if (peek_next_char(state) == '"' || peek_next_char(state) == '$'
				|| peek_next_char(state) == '\\')
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
		return (push_escaped_substr(state, start, state->offset - 1, '"'));
	return (1);
}
