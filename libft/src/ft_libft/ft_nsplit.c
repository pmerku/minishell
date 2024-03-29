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

#include <stddef.h>
#include <ft_memory.h>

static int	count_words(const char *str, char delim, int max)
{
	int		n;
	char	in_word;

	n = 0;
	in_word = 0;
	while (*str != '\0')
	{
		if (*str != delim && !in_word)
		{
			n++;
			in_word = 1;
		}
		if (*str == delim && in_word)
			in_word = 0;
		str++;
	}
	return (n > max ? max : n);
}

static char	read_word(const char *str, char delim, char **arr, int last)
{
	char	*word;
	size_t	len;

	len = 0;
	while (str[len] != '\0' && (str[len] != delim || last))
		len++;
	word = ft_calloc(sizeof(char), (len + 1));
	if (!word)
		return (0);
	while (len > 0)
	{
		word[len - 1] = str[len - 1];
		len--;
	}
	arr[0] = word;
	return (1);
}

char		**ft_nsplit(const char *str, char delim, int max)
{
	int		word_count;
	int		n;
	char	**arr;

	if (!str)
		return (NULL);
	word_count = count_words(str, delim, max);
	arr = ft_calloc(sizeof(char *), (word_count + 1));
	if (!arr)
		return (NULL);
	n = 0;
	while (n < word_count)
	{
		while (*str == delim && *str != '\0')
			str++;
		if (!read_word(str, delim, arr + n, n == max - 1))
			return (ft_free_array(arr));
		while (*str != delim && *str != '\0')
			str++;
		n++;
	}
	return (arr);
}
