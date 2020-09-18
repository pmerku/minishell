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

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stddef.h>

extern size_t	ft_strlen(const char *s);
extern void		*ft_memcpy(void *dst, const void *src, size_t n);
extern char		*ft_strdup(const char *s);
extern int		ft_strcmp(const char *s1, const char *s2);
extern char		*ft_strcpy(char *dst, const char *src);

void			*ft_memset(void *b, int c, size_t len);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const	void *s1, const	void *s2, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin3(char *a, char *b, char *c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strnlen(const char *s, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle, size_t n);
void			ft_strarr_append(char ***arr, char *line);
int				ft_strarr_size(char **arr);

#endif
