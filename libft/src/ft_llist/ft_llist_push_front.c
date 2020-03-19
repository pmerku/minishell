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

#include <ft_llist.h>
#include <ft_memory.h>

char	ft_llist_push_front(t_llist *lst, void *data)
{
	t_llist_node *node;

	ft_nullcheck(lst);
	node = ft_malloc(sizeof(t_llist_node));
	if (node == NULL)
		return (0);
	node->data = data;
	node->next = lst->head;
	lst->head = node;
	return (1);
}
