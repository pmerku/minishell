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

#include <get_next_line.h>
#include <libft.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int		main(void)
{
	int		fd0, fd1;
	char	*line;
	int		res0, res1;

	fd0 = open("main.c", O_RDONLY);
	fd1 = 0;
	res0 = res1 = 1;
	while (res0 > 0 || res1 > 0)
	{
		if (res0 > 0)
		{
			res0 = get_next_line(fd0, &line);
			if (res0 == 0)
				printf("%s", line);
			else
				printf("%s\n", line);
			free(line);
		}
		if (res1 > 0)
		{
			res1 = get_next_line(fd1, &line);
			if (res1 == 0)
				printf("%s", line);
			else
				printf("%s\n", line);
			free(line);
		}
	}
	return (0);
}