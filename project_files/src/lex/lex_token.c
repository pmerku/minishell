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
#include <ft_memory.h>
#include <ft_lex.h>

char		lex_next_to_char(t_lex_state *state, char *c)
{
	*c = lex_next_char(state);
	return (*c);
}

char		create_composite_token(t_lex_state *state, t_composite_string *str)
{
	t_token *token;

	token = ft_malloc(sizeof(t_token));
	if (token == NULL)
		return (0);
	token->str = str;
	token->type = STRING;
	if (!ft_llist_push_back(state->tokens, token))
	{
		del_elem(token);
		return (0);
	}
	return (1);
}

char		create_token(t_lex_state *state, t_token_type type)
{
	t_token *token;

	token = ft_malloc(sizeof(t_token));
	if (token == NULL)
		return (0);
	token->str = NULL;
	token->type = type;
	if (!ft_llist_push_back(state->tokens, token))
	{
		ft_free(token);
		return (0);
	}
	return (1);
}

char		setup_state(char **err, char *str, t_lex_state *state)
{
	ft_bzero(state, sizeof(t_lex_state));
	state->str = str;
	state->tokens = ft_llist_new(&del_elem);
	state->err = err;
	if (state->tokens == NULL)
	{
		*err = "Failed to create linked list";
		return (0);
	}
	return (1);
}
