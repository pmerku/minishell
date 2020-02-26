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

void	linked_list_iter(t_linked_list *lst, void (*f)(void *))
{
	t_linked_list_node *node;

	node = lst->head;
	while (node != NULL)
	{
		f(node->data);
		node = node->next;
	}
}
