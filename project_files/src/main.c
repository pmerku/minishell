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

int		main(void)
{
	char	*line;
	int 	gnl_ret;

	gnl_ret = 1;
	while (gnl_ret == 1)
	{
		ft_printf("&b&l$miniShell > &r");
		gnl_ret = get_next_line(0, &line);
		ft_printf("Execute: %s\n", line);
		ft_free(line);
	}
	return (0);
}