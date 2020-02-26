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

#include <memmgmt.h>
#include <libft.h>

char	*ft_strdup(const char *str)
{
	char *dup;
	char *ptr;

	if (str == NULL)
		return (NULL);
	dup = ft_malloc(sizeof(char) * (ft_strlen(str)));
	ptr = dup;
	while (*str != '\0')
	{
		*ptr = *str;
		str++;
		ptr++;
	}
	*ptr = '\0';
	return (dup);
}
