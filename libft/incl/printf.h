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

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>

/*
** Performs a printf, writing the output to STDOUT
*/
int		ft_printf(const char *str, ...);

/*
** Performs a printf, writing the output to the specified fd
*/
int		ft_fprintf(int fd, const char *str, ...);

/*
** Performs a printf, writing the output to STDOUT, but reads the arguments
** from the va_list of another function
*/
int		ft_vprintf(const char *str, va_list arg);

/*
** Performs a printf, writing the output to the specified fd , but reads the
** arguments from the va_list of another function
*/
int		ft_vprintf(const char *str, va_list arg);

/*
** Performs a printf writing to STDERR, exiting the code afterwards.
**
** This function does use exit, so be sure that exit is not a forbidden
** function in your project.
*/
void	ft_eprintf(int code, const char *str, ...);

#endif
