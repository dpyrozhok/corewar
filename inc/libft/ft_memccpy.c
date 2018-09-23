/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:01:02 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/04 19:01:36 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*srcnew;
	unsigned char	*dstnew;

	srcnew = (unsigned char*)src;
	dstnew = (unsigned char*)dest;
	while (n > 0 && *srcnew != (unsigned char)c)
	{
		n--;
		*dstnew++ = *srcnew++;
	}
	if (n > 0)
	{
		*dstnew++ = *srcnew++;
		return (dstnew);
	}
	else
		return (NULL);
}
