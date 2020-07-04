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

#include <stdlib.h>
#include <ft_stdio/ft_printf.h>
#include <ft_parser.h>
#include <ft_env.h>
#include <zconf.h>
#include <string.h>
#include <ft_exec.h>
#include <ft_string.h>
#include <fcntl.h>
#include <errno.h>
#include <ft_memory.h>

static int	redirections_in_default(t_executor *exec, int prev_fd)
{
	if (prev_fd != 0)
		exec->fd_in = dup(prev_fd);
	return (0);
}

static int	redirections_in_error(char *file)
{
	ft_printf("&cError opening file &f%s&c: &f%s&r\n",
			  file, strerror(errno));
	ft_free(file);
	return (1);
}

int			get_input(t_parser_command *command, t_executor *exec,
		t_env *env, int prev_fd)
{
	size_t			i;
	t_redirection	*redir;
	char 			*file;

	i = 0;
	if (command->redirections_in == NULL)
		return (redirections_in_default(exec, prev_fd));
	exec->fd_in = -1;
	while (command->redirections_in[i] != NULL)
	{
		redir = command->redirections_in[i];
		if (exec->fd_in != -1)
			close(exec->fd_in);
		file = env_parse_string(env, redir->file);
		if (file == NULL)
			return (1);
		exec->fd_in = open(file, O_RDONLY);
		if (exec->fd_in == -1)
			return (redirections_in_error(file));
		ft_free(file);
		i++;
	}
	return (0);
}
