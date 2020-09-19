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

char		lex_next_char(t_lex_state *state)
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

int			is_string_char(char c)
{
	return (c == '\'' || c == '"' || is_non_identifier_char(c));
}

char		is_valid_env_var_char(char c, int is_first_char)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	if ((c >= '0' && c <= '9') && is_first_char == 0)
		return (1);
	return (0);
}

char		*escape_chars(char str_type, char *str)
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
			if (str_type == '"' && (str[cur + 1] == '$' || str[cur + 1] == '`'
				|| str[cur + 1] == '"' || str[cur + 1] == '\\'))
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
