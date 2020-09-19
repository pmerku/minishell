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

#include <ft_memory.h>
#include <ft_lex.h>

char	composite_string_push(t_composite_string **composite, char *str,
		t_token_type type)
{
	t_composite_string	*last;
	t_composite_string	*new_composite;

	new_composite = ft_malloc(sizeof(t_composite_string));
	if (new_composite == NULL)
		return (0);
	new_composite->str = str;
	new_composite->type = type;
	new_composite->next = NULL;
	if (*composite == NULL)
	{
		*composite = new_composite;
	}
	else
	{
		last = *composite;
		while (last->next != NULL)
		{
			last = (t_composite_string *)last->next;
		}
		last->next = (struct t_composite_string *)new_composite;
	}
	return (1);
}

void	del_comp_string(t_composite_string *str)
{
	t_composite_string *tmp;
	t_composite_string *next;

	next = str;
	while (next != NULL)
	{
		tmp = (t_composite_string *)next->next;
		ft_free(next->str);
		ft_free(next);
		next = tmp;
	}
}

void	del_elem(void *ptr)
{
	del_comp_string(((t_token *)ptr)->str);
	ft_free(ptr);
}
