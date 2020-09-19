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

#include <ft_llist.h>
#include <ft_memory.h>
#include <ft_lex.h>

char		lex_other(t_lex_state *state, char c)
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

char		lex_loop(t_lex_state *state)
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

t_llist		*lex(char *str, char **err)
{
	t_lex_state	state;

	if (!setup_state(err, str, &state))
		return (NULL);
	if (!lex_loop(&state))
	{
		ft_llist_free(&state.tokens);
		return (NULL);
	}
	return (state.tokens);
}
