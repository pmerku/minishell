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

static int	redirections_pipes(t_executor *exec, int last_command)
{
	if (pipe(exec->fd_pipe) == -1)
	{
		ft_printf("&cError creating pipes: &f%s&r\n", strerror(errno));
		return(1);
	}
	exec->fd_in = exec->fd_pipe[PIPE_IN];
	exec->fd_out = exec->fd_pipe[PIPE_OUT];
	if (last_command)
	{
		close(exec->fd_out);
		exec->fd_out = exec->tmp_out;
	}
	return (0);
}

static int	redirections_out_error(char *file)
{
	ft_printf("&cError opening file &f%s&c: &f%s&r\n", file, strerror(errno));
	ft_free(file);
	return (1);
}

int			get_output(t_parser_command *command, t_executor *exec,
		t_env *env, int last_command)
{
	size_t			i;
	t_redirection	*redir;
	char 			*file;

	i = 0;
	if (command->redirections_out == NULL)
		return (redirections_pipes(exec, last_command));
	exec->fd_out = -1;
	while (command->redirections_out[i] != NULL)
	{
		redir = command->redirections_out[i];
		if (exec->fd_out != -1)
			close(exec->fd_out);
		file = env_parse_string(env, redir->file);
		if (file == NULL)
			return (1);
		exec->fd_out = open(file, O_WRONLY | O_CREAT | (redir->type == APPEND
			? O_APPEND : O_TRUNC), 0644);
		if (exec->fd_out == -1)
			return (redirections_out_error(file));
		ft_free(file);
		i++;
	}
	return (0);
}
