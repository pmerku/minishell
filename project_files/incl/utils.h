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

#ifndef UTILS_H
# define UTILS_H

# include <ft_exec.h>

void	ft_close(int fd);
int		ft_dup(int fd);
int		ft_dup2(int fd1, int fd2);
int		ft_pipe(int *pipe_dest);

int		exit_helper(char **args, t_executor *exec);
int		error_exit_helper(char **args, t_executor *exec);

#endif
