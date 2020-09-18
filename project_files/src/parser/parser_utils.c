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
#include <ft_memory.h>

int						set_error(char **err, char *msg)
{
	*err = msg;
	return (0);
}

static int				free_parse_command_redir(t_parser_command **commands,
		int i, int j)
{
	while (commands[i]->redirections_in != NULL
			&& commands[i]->redirections_in[j] != NULL)
	{
		ft_free(commands[i]->redirections_in[j]);
		j++;
	}
	return (j);
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
		j = free_parse_command_redir(commands, i, 0);
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
