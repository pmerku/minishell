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

char	*ft_strcpy(char *dst, const char *str)
{
	int n;

	n = 0;
	while (str[n] != '\0')
	{
		dst[n] = str[n];
		n++;
	}
	dst[n] = '\0';
	return (dst);
}
