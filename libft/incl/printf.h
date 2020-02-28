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
# include <stddef.h>

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

/*
** Performs a formatted print, writing to a string. The string will always be
** null-terminated. The print will continue running, even if there is no space
** left in the string. Characters that do not fit in the string anymore will not
** be printed, though.
**
** The entire string will be used, and null-terminated at the last character.
** This means that in reality, `size - 1` characters can be printed to the
** buffer, since the last byte is reserved for the null terminator.
**
** The unsafe counterpart, sprintf, is not added to this library for very
** obvious reasons. We don't want you to cause segfaults and risk having a
** buffer overflow vulnerability.
*/
int		ft_snprintf(char *str, size_t size, const char *fmt, ...);

#endif
