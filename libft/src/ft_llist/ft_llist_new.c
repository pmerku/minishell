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

t_llist		*ft_llist_new(void (*del_fn)(void *))
{
	t_llist *lst;

	lst = ft_malloc(sizeof(t_llist));
	lst->del_fn = del_fn;
	lst->head = NULL;
	return (lst);
}
