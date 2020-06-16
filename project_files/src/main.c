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
#include <signal.h>

static int	is_all_space(char *str)
{
	while (*str != '\0' && ft_isspace(*str))
		str++;
	return (*str == '\0');
}

static void signal_handler(int signo)
{
    char *working_dir;

    if (signo == SIGINT)
    {
        ft_printf("\n");
        working_dir = getcwd(NULL, 0);
        ft_printf("\033[46;37m&f \xF0\x9F\x93\x81 %d %s&r ", 1, working_dir);
        free(working_dir);
        signal(SIGINT, signal_handler);
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
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, SIG_IGN);
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

		execute(parse_tokens, env);

		free_parse_results(parse_tokens);
		ft_llist_free(&lex_tokens);
		ft_free(line);
		free(working_dir);
	}
	ft_free_array(env->vars);
	free(env);
	return (0);
}
