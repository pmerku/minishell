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

static t_composite_string *g_str = NULL;

static int append_empty_argument(t_parser_state *state)
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

static int				handle_token(t_parser_state *state, char **err)
{
	if (state->state == PARSING_COMMAND)
	{
		if (state->current_token->type == STRING && !add_argument(state, state->current_token->str))
			return (set_error(err, "Failed to append argument to cmd"));
		else if (state->current_token->type != STRING && finished_command(state))
			state->state = EXPECTING_TOKEN;
		else if (state->current_token->type != STRING && !finished_command(state))
		{
			if (!append_empty_argument(state))
				return (set_error(err, "Failed to append empty arg to cmd"));
			state->state = EXPECTING_TOKEN;
		}

//		if (state->current_token->type != STRING && finished_command(state))
//			state->state = EXPECTING_TOKEN;
//		else if (state->current_token->type != STRING)
//			return (set_error(err, "Unexpected token (string expected)"));
//		else if (!add_argument(state, state->current_token->str))
//			return (set_error(err, "Failed to append argument to cmd"));
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
		{
//			ft_printf("TODO -> Handle token %s\n", token_to_str(state->current_token->type));
			return (set_error(err, "Unsupported token\n"));
		}
	}
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

/*
** NOTE: We do NOT free ANY kind of t_composite_string, as these are cleared
** when clearing the lexer result!
*/
static void				free_parse_command_list(t_parser_command **commands)
{
	size_t i;
	size_t j;

	if (commands == NULL)
		return ;
	i = 0;
	while (commands[i] != NULL)
	{
		j = 0;
		while (commands[i]->redirections_in != NULL
			   && commands[i]->redirections_in[j] != NULL)
		{
			ft_free(commands[i]->redirections_in[j]);
			j++;
		}
		j = 0;
		if (commands[i]->redirections_in != NULL)
			ft_free(commands[i]->redirections_in);
		while (commands[i]->redirections_out != NULL
			   && commands[i]->redirections_out[j] != NULL)
		{
			ft_free(commands[i]->redirections_out[j]);
			j++;
		}
		if (commands[i]->redirections_out != NULL)
			ft_free(commands[i]->redirections_out);
		if (commands[i]->arguments != NULL)
			ft_free(commands[i]->arguments);
		ft_free(commands[i]);
		i++;
	}
	ft_free(commands);
}

/*
** NOTE: We do NOT free ANY kind of t_composite_string, as these are cleared
** when clearing the lexer result!
*/
void					free_parse_results(t_parser_command ***commands)
{
	size_t i;

	if (commands == NULL)
		return ;
	i = 0;
	while (commands[i] != NULL)
	{
		free_parse_command_list(commands[i]);
		i++;
	}
	ft_free(commands);
	if (g_str != NULL) {
		if (g_str->str != NULL)
			g_str->str = ft_free(g_str->str);
		g_str = ft_free(g_str);
	}
}

t_parser_command 		***parse(t_llist *tokens, char **err)
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
	if (state.current_token->type == PIPE)
	{
		free_parse_results(state.commands);
		*err = "Command expected after '|', got NULL";
		return (NULL);
	}
	return (state.commands);
}
