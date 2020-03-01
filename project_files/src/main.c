/* ************************************************************************** */
/*                                                                            */
/*   Project: project_files                                   ::::::::            */
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
#include <lex.h>
#include <ft_env.h>
#include <unistd.h>

// literally just for env variable parsing testing
// remove this once they work
void	debug_tokens(t_linked_list *lst, t_env *env)
{
	t_linked_list_node	*node;
	t_token				*token;

	node = lst->head;
	while (node != NULL)
	{
		token = (t_token *)node->data;
		if (token->type == STRING)
		{
			ft_printf(" &a&l* &rParsed compound string: %s\n", env_parse_string(env, token->str));
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
	env_print_all(env);
	(void)argc;
	(void)argv;
	gnl_ret = 1;
	while (gnl_ret == 1)
	{
		working_dir = getcwd(NULL, 60);
		ft_printf("\033[46;37m&f \xF0\x9F\x93\x81 %s&r ", working_dir);
		gnl_ret = get_next_line(0, &line);
		lex_tokens = lex(line);
		debug_tokens(lex_tokens, env);
		ft_free(line);
	}
	return (0);
}