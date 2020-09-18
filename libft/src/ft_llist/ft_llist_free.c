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
