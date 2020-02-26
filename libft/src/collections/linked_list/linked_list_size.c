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

#include <linked_list.h>
#include <stddef.h>

int						linked_list_size(t_linked_list *lst)
{
	t_linked_list_node	*node;
	int					i;

	i = 0;
	node = lst->head;
	while (node != NULL)
	{
		node = node->next;
		i++;
	}
	return (i);
}
