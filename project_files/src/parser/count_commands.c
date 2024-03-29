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

size_t			count_command_args(t_parser_command *cmd)
{
	size_t i;

	if (cmd->arguments == NULL)
		return (0);
	i = 0;
	while (cmd->arguments[i] != NULL)
		i++;
	return (i);
}

size_t			count_command_redirections(t_redirection **arr)
{
	size_t i;

	if (arr == NULL)
		return (0);
	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

int				count_commands(t_parser_state *state)
{
	size_t i;

	if (state->commands == NULL)
		return (0);
	i = 0;
	while (state->commands[i] != NULL)
		i++;
	return (i);
}
