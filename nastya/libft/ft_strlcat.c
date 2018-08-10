/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 19:40:26 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/06 20:23:36 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		d;
	size_t		s;
	size_t		i;
	size_t		j;
	size_t		size;

	d = ft_strlen(dst);
	s = ft_strlen(src);
	i = 0;
	j = d;
	size = dstsize;
	while (size > d + 1)
	{
		dst[j++] = src[i++];
		size--;
	}
	dst[j] = '\0';
	if (d > dstsize)
		return (dstsize + s);
	return (d + s);
}
