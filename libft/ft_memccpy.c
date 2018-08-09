/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:23:19 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:04:53 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*buf_d;
	unsigned char	*buf_s;
	size_t			i;

	buf_d = (unsigned char *)dst;
	buf_s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*(buf_d + i) = *(buf_s + i);
		if (*(buf_s + i) == (unsigned char)c)
			return ((buf_d + i + 1));
		i++;
	}
	return (NULL);
}
