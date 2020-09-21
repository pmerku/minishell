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

#include <ft_env.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ft_exec.h>
#include <sys/wait.h>
#include <ft_errno.h>

void		exit_codes(t_executor *exec, t_env *env)
{
	while ((exec->last_pid = waitpid(0, &exec->status, WUNTRACED)) > 0)
	{
		if (exec->last_pid == exec->pid)
		{
			if (WIFEXITED(exec->status))
				env->last_status = WEXITSTATUS(exec->status);
			else if (WIFSIGNALED(exec->status))
			{
				env->last_status = WTERMSIG(exec->status);
				env->last_status += SIGNAL_TERMINATED;
			}
		}
	}
}
