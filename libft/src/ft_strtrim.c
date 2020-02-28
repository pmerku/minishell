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
#include <memmgmt.h>

char		*ft_strtrim(const char *s1, const char *set)
{
	unsigned int start;
	unsigned int end;
	unsigned int endi;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strempty());
	start = 0;
	endi = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end >= start && ft_strchr(set, s1[end - endi]) != NULL)
		endi++;
	if (start + endi > end)
		return (ft_strempty());
	return (ft_substr(s1, start, ft_strlen(s1) - start - endi));
}
