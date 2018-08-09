/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 16:12:43 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:05:41 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*buf_d;
	char	*buf_s;

	buf_d = (char *)dst;
	buf_s = (char *)src;
	if (buf_d <= buf_s || buf_d >= buf_s + len)
	{
		while (len--)
			*(buf_d++) = *(buf_s++);
	}
	else if (buf_d > buf_s)
	{
		while (len--)
			*(buf_d + len) = *(buf_s + len);
	}
	return (dst);
}
