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

#include <ft_lex.h>

char			peek_next_char(t_lex_state *state)
{
	if (state->str[state->offset] == '\0')
	{
		return ('\0');
	}
	return (state->str[state->offset]);
}

void			skip_next_char(t_lex_state *state)
{
	if (state->str[state->offset] == '\0')
		return ;
	state->offset++;
}

int				is_non_identifier_char(char c)
{
	if (c == ' ' || c == '|' || c == '\'' || c == '"' || c == '>' || c == '<'
		|| c == '&' || c == ';')
		return (0);
	return (1);
}
