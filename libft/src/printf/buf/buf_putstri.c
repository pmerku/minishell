/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buf_putstri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvoort <dvoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 14:12:56 by dvoort         #+#    #+#                */
/*   Updated: 2020/01/29 14:13:16 by dvoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

void				buf_putstri(t_buf *buf, char *s, size_t n)
{
	buf->putstri(buf->metadata, s, n);
}
