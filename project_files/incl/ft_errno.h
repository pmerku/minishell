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

#ifndef FT_ERRNO_H
# define FT_ERRNO_H

# define DEFAULT			0
# define PIPE_ERROR			1
# define CLOSE_ERROR		2
# define DUP_ERROR			3
# define DUP2_ERROR			4
# define MALLOC_ERROR		5
# define SIGNAL_ERROR		6
# define COMMAND_NOT_FOUND	127
# define SIGNAL_TERMINATED	128

typedef struct		s_error_list
{
	int		index;
	char 	*error_str;
}					t_error_list;

extern int	g_errno;

void	set_errno(int errno_value);
int		get_errno(void);
char	*ft_strerror(int errno_value);

#endif