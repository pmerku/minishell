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

#include <ft_stdio/ft_printf.h>
#include <ft_parser.h>
#include <ft_env.h>
#include <sys/types.h>
#include <zconf.h>
#include <stdlib.h>
#include <ft_exec.h>
#include <ft_string.h>
#include <sys/wait.h>
#include <ft_memory.h>
#include <builtins.h>

static t_builtin_list	g_builtin_list[] = {
		{"echo", builtin_echo},
		{"cd", builtin_cd},
		{"pwd", builtin_pwd},
		{"export", builtin_export},
		{"unset", builtin_unset},
		{"env", builtin_env},
		{"exit", builtin_exit},
};

static int				handle_args(t_executor *exec,
		t_parser_command *command, t_env *env)
{
	exec->args = parse_args(command, env);
	if (exec->args == NULL)
	{
		ft_printf("&cFailed to parse args with env vars\n&r");
		return (exit_helper(exec->args, exec));
	}
	return (0);
}

static int				builtin_search(t_executor *exec, t_env *env)
{
	size_t	j;

	j = 0;
	while (j < sizeof(g_builtin_list) / sizeof(g_builtin_list[0])) {
		if (ft_strcmp(exec->args[0], g_builtin_list[j].name) == 0) {
			g_builtin_list[j].func(exec->args, env);
			return (1);
		}
		j++;
	}
	return (0);
}

static int				exec_command(t_parser_command **list, t_env *env)
{
	t_executor			exec;
	t_parser_command 	*command;
	size_t				i;

	i = 0;
	ft_bzero(&exec, sizeof(exec));
	if (list == NULL || list[0] == NULL)
		return (0);
	exec.tmp_in = dup(STANDARD_IN);
	exec.tmp_out = dup(STANDARD_OUT);
	while (list[i] != NULL)
	{
		command = list[i];
		dup2(exec.fd_in, STANDARD_IN);
		close(exec.fd_in);
		if (handle_args(&exec, command, env) != 0)
			return (EXIT_FAILURE);
		if (get_input(command, &exec, env, i == 0 ? exec.tmp_in : exec.fd_out) != 0)
			return (exit_helper(exec.args, &exec));
		if (get_output(command, &exec, env, list[i + 1] == NULL) != 0)
			return (exit_helper(exec.args, &exec));
		dup2(exec.fd_out, STANDARD_OUT);
		close(exec.fd_out);
		if (builtin_search(&exec, env) == 0)
			exec_fork(&exec, exec.args, env);
		exec.args = ft_free_array(exec.args);
		i++;
	}
	exit_helper(exec.args, &exec);
	waitpid(exec.pid, &exec.status, WUNTRACED);
	if (WIFEXITED(exec.status))
		env->last_status = WEXITSTATUS(exec.status);
	else if (WIFSIGNALED(exec.status))
	{
		env->last_status = WTERMSIG(exec.status);
		env->last_status += SIGNAL_TERMINATED;
	}
	return (EXIT_SUCCESS);
}

int						execute(t_parser_command ***commands, t_env *env)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < exec_num_commands(commands)) {
		ret = exec_command(commands[i], env);
		i++;
	}
	return (ret);
}
