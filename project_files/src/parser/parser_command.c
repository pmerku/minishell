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

/*
** Checks if the parser has parsed at least one argument in the current command.
*/
int 				finished_command(t_parser_state *state)
{
	if (state->current_command == NULL)
		return (0);
	if (state->current_command->arguments == NULL)
		return (0);
	return (state->current_command->arguments[0] != NULL);
}

int				start_new_command(t_parser_state *state, char **err)
{
	t_parser_command	*new_command;
	t_parser_command	**new_array;
	size_t				size;
	size_t 				command_count;

	new_command = ft_calloc(1, sizeof(t_parser_command));
	if (new_command == NULL)
		return (set_error(err, "new_command malloc failed"));
	size = 0;
	command_count = count_commands(state);
	while (state->commands[command_count - 1][size] != NULL)
		size++;
	new_array = ft_calloc(size + 2, sizeof(t_parser_command *));
	if (new_array == NULL)
	{
		ft_free(new_command);
		return (set_error(err, "new_array malloc failed"));
	}
	ft_memmove(new_array, state->commands[command_count - 1], size * 8);
	new_array[size] = new_command;
	ft_free(state->commands[command_count - 1]);
	state->commands[command_count - 1] = new_array;
	state->current_command = new_command;
	return (1);
}
