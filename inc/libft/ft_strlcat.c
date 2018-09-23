/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 12:58:36 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/04 12:59:27 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	dstlen;
	size_t	woop;
	size_t	srclen;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	woop = dstlen;
	if (dstlen > n)
		return (srclen + n);
	while (*src != '\0' && (dstlen + 1) < n)
	{
		dst[dstlen] = *src;
		src++;
		dstlen++;
	}
	dst[dstlen] = '\0';
	return (srclen + woop);
}
