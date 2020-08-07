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

#include <ft_parser.h>

static int		expecting_token(t_parser_state *state, char **err)
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
	return (1);
}

int				handle_token(t_parser_state *state, char **err)
{
	if (state->state == PARSING_COMMAND)
	{
		if (state->current_token->type != STRING && finished_command(state))
			state->state = EXPECTING_TOKEN;
		else if (state->current_token->type != STRING)
			return (set_error(err, "Unexpected token (string expected)"));
		else if (!add_argument(state, state->current_token->str))
			return (set_error(err, "Failed to append argument to cmd"));
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
		return (expecting_token(state, err));
	return (1);
}
