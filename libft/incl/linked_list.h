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

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

typedef struct			s_linked_list
{
	void						(*del_fn)(void *);
	void						*head;
}						t_linked_list;

/*
** Private struct - don't use.
*/
typedef struct			s_linked_list_node
{
	void						*data;
	struct s_linked_list_node	*next;
}						t_linked_list_node;

t_linked_list			*linked_list_new(void (*del_fn)(void *));
void					linked_list_push(t_linked_list *lst, void *data);
void					linked_list_push_back(t_linked_list *lst, void *data);
int						linked_list_size(t_linked_list *lst);

/*
** FREES the linked list, setting the list to null
*/
void					linked_list_free(t_linked_list **lst);

/*
** CLEARS the linked list, not setting the list to null, but removing all
** entries
*/
void					linked_list_clear(t_linked_list *lst);

void					linked_list_iter(t_linked_list *lst, void (*f)(void *));

#endif
