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

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

void			ft_memset(void *ptr, size_t n, char c);
void			ft_bzero(void *ptr, size_t n);

char			*ft_strdup(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
extern size_t   ft_strlen(const char *str);
char			**ft_split(const char *str, char delim);
char			**ft_nsplit(const char *str, char delim, int max);
char			**ft_strarr_free(char **arr);
int				ft_strarr_size(char **arr);
char			ft_strends_with(const char *str, const char *end);
void			ft_strarr_append(char ***arr, char *str);
int				ft_stris_empty(const char *str);
char			*ft_strempty(void);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_strchr(const char *s, int c);
extern char		*ft_strcpy(char *dst, const char *str);

int				ft_isspace(char c);
int				ft_isdigit(char c);

int				ft_abs(int n);
double			ft_dabs(double n);
int				ft_min(int a, int b);
int				ft_max(int a, int b);
int				ft_atoi(const char *str);

#endif
