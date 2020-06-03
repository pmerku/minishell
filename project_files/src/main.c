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

#include <ft_exec.h>
#include <ft_llist.h>
#include <ft_libft.h>
#include <ft_stdio/ft_printf.h>
#include <ft_memory.h>
#include <ft_lex.h>
#include <ft_env.h>
#include <unistd.h>
#include <stdlib.h>
#include <ft_parser.h>
#include <ft_ctype.h>

static int	is_all_space(char *str)
{
	while (*str != '\0' && ft_isspace(*str))
		str++;
	return (*str == '\0');
}

static void visualize_parse(t_parser_command ***commands, t_env *env)
{
	if(1)return;

	t_parser_command	**list;
	t_parser_command	*command;
	t_redirection		**redirections;
	size_t				i;
	char 				*parsed_string;

	ft_printf("&fParse results:&r %p\n", commands);
	while (*commands != NULL) {
		ft_printf("&a  * &fCommand execution\n");
		list = *commands;
		while (*list != NULL) {
			ft_printf("&a    * &fSingle command\n");
			ft_printf("&a      * &fArguments:\n");
			command = *list;
			i = 0;
			while (command->arguments[i] != NULL) {
				parsed_string = env_parse_string(env, command->arguments[i++]);
				ft_printf("&e        - '&f%s&e'\n&r", parsed_string);
				ft_free(parsed_string);
			}
			i = 0;
			redirections = command->redirections_in;
			while (redirections != NULL && redirections[i] != NULL) {
				if (i == 0)
					ft_printf("&a      * &fRedirections (In):\n");
				parsed_string = env_parse_string(env, redirections[i++]->file);
				ft_printf("&e        - &f%s\n&r", parsed_string);
				ft_free(parsed_string);
			}
			redirections = command->redirections_out;
			while (redirections != NULL && redirections[i] != NULL) {
				if (i == 0)
					ft_printf("&a      * &fRedirections (Out):\n");
				parsed_string =  env_parse_string(env, redirections[i]->file);
				ft_printf("&e        - &f%s (&eType: &f%s)\n&r", parsed_string, redirections[i]->type == APPEND ? "APPEND" : "TRUNCATE");
				ft_free(parsed_string);
				i++;
			}
			list++;
		}
		commands++;
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*line;
	int 	gnl_ret;
	t_llist	*lex_tokens;
	t_parser_command ***parse_tokens;
	char 	*working_dir;

	char 	*err = NULL;

	env = env_from(envp);
	(void)argc;
	(void)argv;
	gnl_ret = 1;
	while (gnl_ret == 1)
	{
		working_dir = getcwd(NULL, 0);
		ft_printf("\033[46;37m&f \xF0\x9F\x93\x81 %d %s&r ", 1, working_dir);
		gnl_ret = get_next_line(0, &line);
		if (gnl_ret < 0)
		{
			ft_printf("&cget_next_line error&r\n");
			free(working_dir);
		}
		if (is_all_space(line))
		{
			ft_free(line);
			free(working_dir);
			continue ;
		}
		lex_tokens = lex(line, &err);
		if (err != NULL)
		{
			ft_printf("&cError lexing:&r %s\n", err);
			err = NULL;
			ft_free(line);
			free(working_dir);
			continue ;
		}
		parse_tokens = parse(lex_tokens, &err);
		if (err != NULL)
		{
			ft_printf("&cError parsing:&r %s\n", err);
			err = NULL;
			ft_llist_free(&lex_tokens);
			ft_free(line);
			free(working_dir);
			continue ;
		}
		visualize_parse(parse_tokens, env);

		execute(parse_tokens, env);
//		ft_printf("EXECUTE RETURN: [%d]\n", execute(parse_tokens, env));


		free_parse_results(parse_tokens);
		ft_llist_free(&lex_tokens);
		ft_free(line);
		free(working_dir);
	}
	return (0);
}
