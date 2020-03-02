/* ************************************************************************** */
/*                                                                            */
/*   Project: github_minishell                            ::::::::            */
/*   Members: dvoort, prmerku                           :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <libft.h>
#include <get_next_line.h>
#include <memmgmt.h>

static int	clean(int fd, char *store[fd], int x)
{
	if (store[fd] && x == -1)
	{
		ft_free(store[fd]);
		store[fd] = NULL;
	}
	return (x);
}

static int	ft_read(int fd, char *store[fd])
{
	char	*tmp;
	char	buf[BUFFER_SIZE + 1];
	int		res;

	res = read(fd, buf, BUFFER_SIZE);
	if (res < 0)
		return (-1);
	buf[res] = '\0';
	if (!store[fd])
		store[fd] = ft_strdup(buf);
	else
	{
		tmp = store[fd];
		store[fd] = ft_strjoin(tmp, buf);
		ft_free(tmp);
	}
	if (!store[fd])
		return (clean(fd, store, -1));
	return (res);
}

int			get_next_line(int fd, char **line)
{
	char		*tmp;
	char		*ptr;
	static char	*store[INT_MAX];
	int			res;

	if (BUFFER_SIZE <= 0 || !line)
		return (-1);
	res = 1;
	while (!ft_strchr(store[fd], '\n') && res > 0)
		res = ft_read(fd, store);
	if (res < 0)
		return (-1);
	ptr = ft_strchr(store[fd], '\n');
	if (ptr != NULL)
	{
		*ptr = '\0';
		*line = ft_strdup(store[fd]);
		tmp = store[fd];
		store[fd] = ft_strdup(ptr + 1);
		ft_free(tmp);
		return ((!(*line) || !store[fd]) ? clean(fd, store, -1) : 1);
	}
	*line = ft_strdup(store[fd]);
	clean(fd, store, -1);
	return ((!(*line)) ? -1 : 0);
}
