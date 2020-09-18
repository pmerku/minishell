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

#ifndef FT_LIBFT_H
# define FT_LIBFT_H

# define BASE_SET "0123456789ABCDEF"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# include <stddef.h>

char	*ft_itoa(int n);
int		ft_intlen(int n);
char	*ft_itoa_base(int n, int base);
int		ft_intlen_base(int n, int base);
char	**ft_split(const char *str, char delim);
char	**ft_nsplit(const char *str, char delim, int max);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strempty(void);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strip_chars(char *str, char c);
int		get_next_line(int fd, char **line);

#endif
