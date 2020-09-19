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

#include <ft_errno.h>
#include <stddef.h>

int		g_errno = DEFAULT;

void	set_errno(int errno_value)
{
	g_errno = errno_value;
}

int		get_errno(void)
{
	return (g_errno);
}

static t_error_list	g_error_list[] = {
	{PIPE_ERROR, "Can't create pipe"},
	{CLOSE_ERROR, "Can't close file or file doesn't exist"},
	{DUP_ERROR, "Can't create new file descriptor"},
	{DUP2_ERROR, "Can't create new file descriptor"},
	{MALLOC_ERROR, "Can't allocate memory"},
	{SIGNAL_ERROR, "Can't catch user signal"}
};

char	*ft_strerror(int errno_value)
{
	size_t j;

	j = 0;
	while (j < sizeof(g_error_list) / sizeof(g_error_list[0]))
	{
		if (errno_value == g_error_list[j].index)
		{
			return (g_error_list[j].error_str);
		}
		j++;
	}
	return ("Unknown error");
}
