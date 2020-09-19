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
#include <ft_stdio/ft_printf.h>

int			add_argument(t_parser_state *state, t_composite_string *str)
{
	size_t				size;
	t_composite_string	**new;

	if (state->current_command == NULL)
	{
		ft_printf("&cGot NULL where it should never be NULL :O&r\n");
		return (0);
	}
	size = count_command_args(state->current_command);
	new = ft_calloc(size + 2, sizeof(t_parser_command *));
	if (new == NULL)
		return (0);
	ft_memmove(new, state->current_command->arguments, size * 8);
	new[size] = str;
	ft_free(state->current_command->arguments);
	state->current_command->arguments = new;
	return (1);
}

static int	append_redirection(t_parser_state *state, t_composite_string *str,
			t_redirection_type type)
{
	t_redirection		*redirection;
	t_redirection		***arr;
	t_redirection		**new;
	t_parser_command	*command;
	size_t				size;

	redirection = ft_malloc(sizeof(t_redirection));
	if (redirection == NULL)
		return (0);
	redirection->type = type;
	redirection->file = str;
	command = state->current_command;
	arr = type == IN ? &command->redirections_in : &command->redirections_out;
	size = count_command_redirections(*arr);
	new = ft_calloc(size + 2, sizeof(t_redirection *));
	if (new == NULL)
	{
		ft_free(redirection);
		return (0);
	}
	ft_memmove(new, *arr, size * 8);
	new[size] = redirection;
	ft_free(*arr);
	*arr = new;
	return (1);
}

int			add_redirection(t_parser_state *state, t_composite_string *str)
{
	t_redirection_type type;

	if (state->previous_token->type == REDIR_R)
		type = TRUNCATE;
	else if (state->previous_token->type == REDIR_RR)
		type = APPEND;
	else if (state->previous_token->type == REDIR_L)
		type = IN;
	else
		return (0);
	return (append_redirection(state, str, type));
}

int			is_redir_token(t_token_type type)
{
	return (type == REDIR_R || type == REDIR_RR || type == REDIR_L);
}
