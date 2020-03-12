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

char        *ft_substr(const char *s, unsigned int start, size_t len)
{
    char            *block;
    unsigned int    i;

    if (len == 0 || start > ft_strlen(s))
        return (ft_strempty());
    if (s == NULL)
        return (NULL);
    if (len > ft_strlen(s) - start)
        len = ft_strlen(s) - start;
    block = ft_malloc((len + 1) * sizeof(char));
    if (block == NULL)
        return (NULL);
    i = 0;
    while (i < len)
    {
        block[i] = s[start + i];
        i++;
    }
    block[i] = '\0';
    return (block);
}
