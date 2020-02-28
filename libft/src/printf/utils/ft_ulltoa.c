/* ************************************************************************** */
/*                                                                            */
/*   Project: project_files                                   ::::::::            */
/*   Members: dvoort, prmerku                           :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static void		ft_ulltoa_inner(char *out, unsigned long long value, int *i)
{
	if (value > 9)
		ft_ulltoa_inner(out, value / 10, i);
	out[*i] = '0' + (value % 10);
	(*i)++;
}

void			ft_ulltoa(char *out, unsigned long long value)
{
	int i;

	if (value == 0)
	{
		out[0] = '0';
		return ;
	}
	i = 0;
	ft_ulltoa_inner(out, value, &i);
}
