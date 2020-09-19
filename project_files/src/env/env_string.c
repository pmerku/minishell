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

#include <ft_string.h>
#include <ft_env.h>
#include <ft_libft.h>
#include <ft_memory.h>

static char	*composite_to_string(t_env *env, t_composite_string *string)
{
	char *env_value;

	if (string->type == STRING)
	{
		return (ft_strdup(string->str));
	}
	else
	{
		if (ft_strcmp(string->str, "?") == 0)
			return (ft_itoa(env->last_status));
		env_value = env_get(env, string->str);
		return (ft_strdup(env_value == NULL ? "" : env_value));
	}
}

char		*env_parse_string(t_env *env, t_composite_string *string)
{
	char	*joined;
	char	*tmp;
	char	*to_join;

	env_get(env, "SHELL");
	joined = NULL;
	while (string != NULL)
	{
		to_join = ft_nullcheck(composite_to_string(env, string));
		if (joined == NULL)
			joined = to_join;
		else
		{
			tmp = joined;
			joined = ft_strjoin(joined, to_join);
			ft_free(to_join);
			ft_free(tmp);
		}
		string = (t_composite_string *)string->next;
	}
	return (joined);
}
