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

#include <memmgmt.h>
#include <libft.h>

static int	count_words(const char *str, char delim)
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
	return (n);
}

static char	read_word(const char *str, char delim, char **arr, int n)
{
	char	*word;
	size_t	len;

	len = 0;
	while (str[len] != '\0' && str[len] != delim)
		len++;
	word = ft_malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (0);
	word[len] = '\0';
	while (len > 0)
	{
		word[len - 1] = str[len - 1];
		len--;
	}
	arr[n] = word;
	return (1);
}

char		**ft_split(const char *str, char delim)
{
	int		word_count;
	int		n;
	char	**arr;

	if (str == NULL)
		return (NULL);
	word_count = count_words(str, delim);
	arr = ft_malloc(sizeof(char *) * (word_count + 1));
	ft_bzero(arr, sizeof(char *) * (word_count + 1));
	if (arr == NULL)
		return (NULL);
	n = 0;
	while (n < word_count)
	{
		while (*str == delim && *str != '\0')
			str++;
		if (!read_word(str, delim, arr, n))
			return (ft_strarr_free(arr));
		while (*str != delim && *str != '\0')
			str++;
		n++;
	}
	return (arr);
}
