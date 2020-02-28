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

#include <linked_list.h>
#include <memmgmt.h>

void					linked_list_clear(t_linked_list *lst)
{
	t_linked_list_node *next;
	t_linked_list_node *node;

	if (lst == NULL)
		return ;
	node = lst->head;
	while (node != NULL)
	{
		next = node->next;
		lst->del_fn(node->data);
		ft_free(node);
		node = next;
	}
	lst->head = NULL;
}
