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

#include <ft_parser.h>
#include <ft_memory.h>
#include <ft_string.h>

t_composite_string *g_str = NULL;

static int		append_empty_argument(t_parser_state *state)
{
	g_str = ft_calloc(1, sizeof(t_composite_string));
	if (g_str == NULL)
		return (0);
	g_str->type = STRING;
	g_str->str = ft_strdup("");
	if (g_str->str == NULL)
	{
		ft_free(g_str);
		return (0);
	}
	return (add_argument(state, g_str));
}

int				handle_token(t_parser_state *state, char **err)
{
	if (state->state == PARSING_COMMAND)
	{
		if (state->current_token->type == STRING
			&& !add_argument(state, state->current_token->str))
			return (set_error(err, "Failed to append argument to cmd"));
		else if (state->current_token->type != STRING
			&& finished_command(state))
			state->state = EXPECTING_TOKEN;
		else if (state->current_token->type != STRING
			&& !finished_command(state))
		{
			if (!append_empty_argument(state))
				return (set_error(err, "Failed to append empty arg to cmd"));
			state->state = EXPECTING_TOKEN;
		}
	}
	if (state->state == PARSING_FILENAME)
	{
		if (state->current_token->type != STRING)
			return (set_error(err, "Unexpected token (expect filename)"));
		if (!add_redirection(state, state->current_token->str))
			return (set_error(err, "Failed to append redirection to cmd"));
		state->state = EXPECTING_TOKEN;
	}
	else if (state->state == EXPECTING_TOKEN)
	{
		if (state->current_token->type == SEMICOLUMN
			|| state->current_token->type == PIPE)
			state->state = PARSING_COMMAND;
		if (is_redir_token(state->current_token->type))
			state->state = PARSING_FILENAME;
		else if (state->current_token->type == SEMICOLUMN)
			return (start_new_execution(state, err));
		else if (state->current_token->type == PIPE)
			return (start_new_command(state, err));
		else
			return (set_error(err, "Unsupported token\n"));
	}
	return (1);
}
