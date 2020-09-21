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

#include <ft_stdio/ft_printf.h>
#include <ft_parser.h>
#include <ft_env.h>
#include <string.h>
#include <ft_exec.h>
#include <ft_string.h>
#include <fcntl.h>
#include <errno.h>
#include <ft_memory.h>

static int	fd_error(char **file)
{
	ft_printf("&cError opening &f%s&c: &f%s&r\n", *file, strerror(errno));
	ft_free(*file);
	*file = NULL;
	return (-3);
}

int			get_in_fd(t_parser_command *command, t_env *env)
{
	size_t			i;
	t_redirection	*redir;
	char			*file;
	int				fd;

	if (command->redirections_in == NULL)
		return (-1);
	i = 0;
	while (command->redirections_in[i] != NULL)
	{
		redir = command->redirections_in[i];
		file = env_parse_string(env, redir->file);
		if (file == NULL)
			return (-2);
		fd = open(file, O_RDONLY);
		if (fd == -1)
			return (fd_error(&file));
		ft_free(file);
		i++;
	}
	return (fd);
}
