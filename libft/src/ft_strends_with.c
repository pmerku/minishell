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

#include <libft.h>

char	ft_strends_with(const char *str, const char *end)
{
	size_t str_len;
	size_t end_len;

	if (str == NULL || end == NULL)
		return (0);
	str_len = ft_strlen(str);
	end_len = ft_strlen(end);
	if (end_len > str_len)
		return (0);
	str += str_len - end_len;
	while (*str != '\0' && *end != '\0' && *str == *end)
	{
		str++;
		end++;
	}
	return (*str == '\0' && *end == '\0');
}
