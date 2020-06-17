/* ************************************************************************** */
/*                                                                            */
/*   Project: custom_libc                                 ::::::::            */
/*   Members: dvoort, prmerku                           :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_memory.h>
#include <ft_string.h>
#include <ft_unistd.h>
#include <ft_libft.h>

static int	clean(int fd, char **store)
{
	if (store[fd])
	{
		ft_free(store[fd]);
		store[fd] = NULL;
	}
	return (-1);
}

static int	ft_read_line(int fd, char **store)
{
	char	*tmp;
	char	buf[BUFFER_SIZE + 1];
	int		res;

	res = ft_read(fd, buf, BUFFER_SIZE);
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
		return (clean(fd, store));
	return (res);
}

int			get_next_line(int fd, char **line)
{
	char		*tmp;
	char		*ptr;
	static char	*store[10400];
	int			res;

	if (BUFFER_SIZE <= 0 || !line)
		return (-1);
	res = 1;
	while (!ft_strchr(store[fd], '\n') && res > 0)
		res = ft_read_line(fd, store);
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
		return ((!(*line) || !store[fd]) ? clean(fd, store) : 1);
	}
	*line = ft_strdup(store[fd]);
	clean(fd, store);
	return ((!(*line)) ? -1 : 0);
}
