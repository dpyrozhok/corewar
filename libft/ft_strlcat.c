/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:15:09 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:12:28 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(dst);
	if (dstsize <= i)
		return (dstsize + ft_strlen(src));
	if (i + ft_strlen(src) < dstsize)
	{
		while (src[j])
			dst[i++] = src[j++];
		dst[i] = '\0';
		return (i);
	}
	else
	{
		while (i < dstsize - 1)
			dst[i++] = src[j++];
		dst[dstsize - 1] = '\0';
		return (ft_strlen(src) - j + i);
	}
}
