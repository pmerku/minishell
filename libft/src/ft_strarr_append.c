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

#include <libft.h>
#include <memmgmt.h>
#include <printf.h>

void			ft_strarr_append(char ***arr, char *line)
{
	char	**new_arr;
	int		i;

	if (*arr == NULL)
	{
		*arr = ft_checked_calloc(sizeof(char *) * 2);
		(*arr)[0] = line;
		return ;
	}
	new_arr = ft_checked_calloc(sizeof(char *) * (ft_strarr_size(*arr) + 2));
	if (new_arr != NULL)
	{
		i = 0;
		while ((*arr)[i] != NULL)
		{
			new_arr[i] = (*arr)[i];
			i++;
		}
		new_arr[i] = line;
	}
	ft_free(*arr);
	*arr = new_arr;
	return ;
}
