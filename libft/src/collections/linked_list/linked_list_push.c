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

void	linked_list_push(t_linked_list *lst, void *data)
{
	t_linked_list_node *node;

	ft_nullcheck(lst);
	node = ft_checked_malloc(sizeof(t_linked_list_node));
	node->data = data;
	node->next = lst->head;
	lst->head = node;
}
