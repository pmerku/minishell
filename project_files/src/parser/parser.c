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
#include <ft_parser.h>
#include <ft_memory.h>
#include <ft_string.h>

static int				return_error(t_parser_command *new_command,
		t_parser_command **new_array, char **err)
{
	ft_free(new_command);
	ft_free(new_array);
	return (set_error(err, "new_commands malloc fail"));
}

int						start_new_execution(t_parser_state *state, char **err)
{
	t_parser_command *new_command;
	t_parser_command **new_array;
	t_parser_command ***new_commands;

	new_command = ft_calloc(1, sizeof(t_parser_command));
	if (new_command == NULL)
		return (set_error(err, "new_command malloc fail"));
	new_array = ft_calloc(2, sizeof(t_parser_command *));
	if (new_array == NULL)
	{
		ft_free(new_command);
		return (set_error(err, "new_array malloc fail"));
	}
	new_array[0] = new_command;
	new_commands = ft_calloc(count_commands(state) + 2, sizeof(void ***));
	if (new_commands == NULL)
		return (return_error(new_command, new_array, err));
	if (state->commands != NULL)
		ft_memmove(new_commands, state->commands, count_commands(state) * 8);
	new_commands[count_commands(state)] = new_array;
	ft_free(state->commands);
	state->commands = new_commands;
	state->current_command = new_command;
	return (1);
}

static int				flat_iter(t_parser_state *state, t_llist *tokens,
		char **err)
{
	t_llist_node *node;

	node = tokens->head;
	while (node != NULL)
	{
		state->previous_token = state->current_token;
		state->current_token = (t_token *)node->data;
		if (!handle_token(state, err))
			return (0);
		node = node->next;
	}
	if (state->state == PARSING_FILENAME)
		return (set_error(err, "Expected filename, got end of line"));
	return (1);
}

t_parser_command		***parse(t_llist *tokens, char **err)
{
	t_parser_state state;

	ft_bzero(&state, sizeof(t_parser_state));
	state.state = PARSING_COMMAND;
	if (!start_new_execution(&state, err))
		return (0);
	if (!flat_iter(&state, tokens, err))
	{
		free_parse_results(state.commands);
		if (err == NULL)
			*err = "An unknown exception occured parsing... Why...";
		return (NULL);
	}
	if (state.current_token != NULL && state.current_token->type == PIPE)
	{
		free_parse_results(state.commands);
		*err = "Command expected after '|', got NULL";
		return (NULL);
	}
	return (state.commands);
}
