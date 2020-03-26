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

#ifndef FT_LLIST_H
# define FT_LLIST_H

/*
** Private struct - don't use.
*/
typedef struct			s_llist_node
{
	void				*data;
	struct s_llist_node	*next;
}						t_llist_node;

typedef struct			s_llist
{
	void				(*del_fn)(void *);
	t_llist_node		*head;
}						t_llist;

t_llist					*ft_llist_new(void (*del_fn)(void *));
char					ft_llist_push_front(t_llist *lst, void *data);
char					ft_llist_push_back(t_llist *lst, void *data);
int						ft_llist_size(t_llist *lst);

/*
** FREES the linked list, setting the list to null
*/
void					ft_llist_free(t_llist **lst);

/*
** CLEARS the linked list, not setting the list to null, but removing all
** entries
*/
void					ft_llist_clear(t_llist *lst);

void					ft_llist_iter(t_llist *lst, void (*f)(void *));

#endif
