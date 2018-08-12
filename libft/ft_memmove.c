/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:53:42 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/10/31 18:05:18 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*kuda;
	unsigned char	*otkuda;
	size_t			i;

	i = 0;
	kuda = (unsigned char *)dst;
	otkuda = (unsigned char *)src;
	if (src <= dst)
	{
		while (len--)
			kuda[len] = otkuda[len];
	}
	else
	{
		while (i < len)
		{
			kuda[i] = otkuda[i];
			i++;
		}
	}
	return (dst);
}
