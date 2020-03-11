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
#include <ft_memory.h>
#include <ft_llist.h>

void	ft_llist_free(t_llist **lst)
{
	t_llist_node *next;
	t_llist_node *node;

	if (*lst == NULL)
		return ;
	node = (*lst)->head;
	while (node != NULL)
	{
		next = node->next;
		(*lst)->del_fn(node->data);
		ft_free(node);
		node = next;
	}
	ft_free(*lst);
	*lst = NULL;
}
