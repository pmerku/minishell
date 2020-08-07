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

#include <stddef.h>
#include <ft_libft.h>
#include <ft_string.h>
#include <ft_memory.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;

    if (len == 0 || start > ft_strlen(s))
    	return (ft_strempty());
    if (s == NULL)
    	return (NULL);
    if (len > ft_strlen(s) - start)
    	len = ft_strlen(s) - start;
    str = ft_malloc((len + 1) * sizeof(char));
    if (str == NULL)
    	return (NULL);
    ft_memcpy(str, s + start, len);
    str[len] = '\0';
    return (str);
}
