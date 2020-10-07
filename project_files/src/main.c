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
#include <minishell.h>

static t_shell	g_shell = {
	.err = NULL,
	.gnl_ret = 1
};

static int	is_all_space(char *str)
{
	while (*str != '\0' && ft_isspace(*str))
		str++;
	return (*str == '\0');
}

static int	lex_wrapper(t_shell *shell)
{
	shell->lex_tokens = lex(shell->line, &shell->err);
	if (shell->err != NULL)
	{
		ft_printf("&cError lexing:&r %s\n", shell->err);
		shell->err = NULL;
		ft_free(shell->line);
		free(shell->dir);
		return (1);
	}
	return (0);
}

static int	parse_wrapper(t_shell *shell)
{
	shell->parse_tokens = parse(shell->lex_tokens, &shell->err);
	if (shell->err != NULL)
	{
		ft_printf("&cError parsing:&r %s\n", shell->err);
		shell->err = NULL;
		ft_llist_free(&shell->lex_tokens);
		ft_free(shell->line);
		free(shell->dir);
		return (1);
	}
	return (0);
}

static int	input_wrapper(t_shell *shell)
{
	shell->dir = getcwd(NULL, 0);
	ft_printf("\033[46;37m&f \xF0\x9F\x93\x81 %d %s&r ", 1, shell->dir);
	shell->gnl_ret = get_next_line(0, &shell->line);
	if (shell->gnl_ret < 0)
	{
		ft_printf("&cget_next_line error&r\n");
		free(shell->dir);
		return (2);
	}
	if (is_all_space(shell->line))
	{
		ft_free(shell->line);
		free(shell->dir);
		return (1);
	}
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	int		ret;

	g_shell.env = env_from(envp);
	(void)argc;
	(void)argv;
	while (g_shell.gnl_ret == 1)
	{
		signal_init();
		ret = input_wrapper(&g_shell);
		if (ret == 2)
			break ;
		else if (ret == 1)
			continue ;
		if (lex_wrapper(&g_shell) == 1)
			continue ;
		if (parse_wrapper(&g_shell) == 1)
			continue ;
		execute(g_shell.parse_tokens, g_shell.env);
		cleanup(&g_shell);
	}
	ft_printf("exit\n");
	ft_free_array(g_shell.env->vars);
	free(g_shell.env);
	return (0);
}
