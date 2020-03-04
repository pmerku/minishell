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

#include <get_next_line.h>
#include <printf.h>
#include <memmgmt.h>
#include <ft_lex.h>
#include <ft_env.h>
#include <unistd.h>
#include <stdlib.h>

// literally just for env variable parsing testing
// remove this once they work
void	debug_tokens(t_linked_list *lst, t_env *env)
{
	t_linked_list_node	*node;
	t_token				*token;
	char 				*fuck_its_the_leaky_boii;

	node = lst->head;
	while (node != NULL)
	{
		token = (t_token *)node->data;
		if (token->type == STRING)
		{
			fuck_its_the_leaky_boii = env_parse_string(env, token->str);
			ft_printf(" &a&l* &rParsed composite string: %s\n", fuck_its_the_leaky_boii);
			ft_free(fuck_its_the_leaky_boii);
		}
		node = node->next;
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_env			*env;
	char			*line;
	int 			gnl_ret;
	t_linked_list	*lex_tokens;
	char 			*working_dir;

	env = env_from(envp);

	(void)argc;
	(void)envp;
	(void)argv;
	gnl_ret = 1;
	while (gnl_ret == 1)
	{
		working_dir = getcwd(NULL, 0);
		ft_printf("\033[46;37m&f \xF0\x9F\x93\x81 %s&r ", working_dir);
		gnl_ret = get_next_line(0, &line);
		lex_tokens = lex(line);
		debug_tokens(lex_tokens, env);

		if (lex_tokens->head != NULL && ((t_token *)lex_tokens->head->data)->type == STRING)
		{
			char *parsed = env_parse_string(env, ((t_token *)lex_tokens->head->data)->str);
			char *path = env_resolve_path_file(env, parsed);
			ft_printf("Token: %s: %s\n", parsed, path);
			ft_free(parsed);
			ft_free(path);
		}

		linked_list_free(&lex_tokens);
		ft_free(line);
		free(working_dir);
	}
	return (0);
}