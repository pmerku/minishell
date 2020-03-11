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

#include <stddef.h>
#include <ft_llist.h>

int		ft_llist_size(t_llist *lst)
{
	t_llist_node	*node;
	int				i;

	i = 0;
	node = lst->head;
	while (node != NULL)
	{
		node = node->next;
		i++;
	}
	return (i);
}
