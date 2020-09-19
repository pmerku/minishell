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
#include <ft_libft.h>

char		lex_err(t_lex_state *state, char *err)
{
	*(state->err) = err;
	return (0);
}

char		push_substr(t_lex_state *state, size_t start, size_t end,
			t_token_type str_type)
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

char		push_escaped_substr(t_lex_state *state, size_t start, size_t end,
			char type)
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
