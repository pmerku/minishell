/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/26 00:00:00 by anonymous     #+#    #+#                 */
/*   Updated: 2020/08/26 00:00:00 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_llist.h>
#include <ft_memory.h>

char	ft_llist_push_back(t_llist *lst, void *data)
{
	t_llist_node *node;
	t_llist_node *iter;

	ft_nullcheck(lst);
	node = ft_malloc(sizeof(t_llist_node));
	if (node == NULL)
		return (0);
	node->data = data;
	node->next = NULL;
	if (lst->head == NULL)
	{
		lst->head = node;
	}
	else
	{
		iter = lst->head;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = node;
	}
	return (1);
}
