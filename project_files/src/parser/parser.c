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
#include <ft_stdio/ft_printf.h>

//static char 	*token_to_str(t_token_type type)
//{
//	if (type == PIPE)
//		return ("PIPE");
//	else if (type == BRACKET_OPEN)
//		return ("BRACKET_OPEN");
//	else if (type == BRACKET_CLOSE)
//		return ("BRACKET_CLOSE");
//	else if (type == STRING)
//		return ("STRING");
//	else if (type == ENV_STRING)
//		return ("ENV_STRING");
//	else if (type == SEMICOLUMN)
//		return ("SEMICOLUMN");
//	else if (type == REDIR_L)
//		return ("REDIR_L");
//	else if (type == REDIR_R)
//		return ("REDIR_R");
//	else if (type == REDIR_RR)
//		return ("REDIR_RR");
//	else if (type == AMPERSAND)
//		return ("AMPERSAND");
//	else if (type == OR)
//		return ("OR");
//	return ("NULL");
//}

static int				set_error(char **err, char *msg)
{
	*err = msg;
	return (0);
}

static size_t			count_command_args(t_parser_command *cmd)
{
	size_t i;

	if (cmd->arguments == NULL)
		return (0);
	i = 0;
	while (cmd->arguments[i] != NULL)
		i++;
	return (i);
}

static size_t			count_command_redirections(t_redirection **arr)
{
	size_t i;

	if (arr == NULL)
		return (0);
	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

static int 				add_argument(t_parser_state *state, t_composite_string *str)
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

static int				append_redirection(t_parser_state *state, t_composite_string *str, t_redirection_type type)
{
	t_redirection		*redirection;
	t_redirection		***arr;
	t_redirection		**new;
	t_parser_command	*command;
	size_t 				size;

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

static int				add_redirection(t_parser_state *state, t_composite_string *str)
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

/*
** Checks if the parser has parsed at least one argument in the current command.
*/
static int 				finished_command(t_parser_state *state)
{
	if (state->current_command == NULL)
		return (0);
	if (state->current_command->arguments == NULL)
		return (0);
	return (state->current_command->arguments[0] != NULL);
}

static int				is_redir_token(t_token_type type)
{
	return (type == REDIR_R || type == REDIR_RR || type == REDIR_L);
}

static int				count_commands(t_parser_state *state)
{
	size_t i;

	if (state->commands == NULL)
		return (0);
	i = 0;
	while (state->commands[i] != NULL)
		i++;
	return (i);
}

static int				start_new_command(t_parser_state *state, char **err)
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

static int				start_new_execution(t_parser_state *state, char **err)
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
	{
		ft_free(new_command);
		ft_free(new_array);
		return (set_error(err, "new_commands malloc fail"));
	}
	if (state->commands != NULL)
		ft_memmove(new_commands, state->commands, count_commands(state) * 8);
	new_commands[count_commands(state)] = new_array;
	ft_free(state->commands);
	state->commands = new_commands;
	state->current_command = new_command;
	return (1);
}

static int append_empty_argument(t_parser_state *state)
{
	t_composite_string *str;

	str = ft_calloc(1, sizeof(t_composite_string));
	if (str == NULL)
		return (0);
	str->type = STRING;
	str->str = ft_strdup("");
	if (str->str == NULL)
	{
		ft_free(str);
		return (0);
	}
	return (add_argument(state, str));
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