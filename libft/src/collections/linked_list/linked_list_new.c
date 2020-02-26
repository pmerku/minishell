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
#include <memmgmt.h>

t_linked_list	*linked_list_new(void (*del_fn)(void *))
{
	t_linked_list *lst;

	lst = ft_checked_malloc(sizeof(t_linked_list));
	lst->del_fn = del_fn;
	lst->head = NULL;
	return (lst);
}
