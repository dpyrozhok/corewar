/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:37:52 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/10/31 16:55:39 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*kuda;
	unsigned char	*otkuda;

	kuda = (unsigned char *)dest;
	otkuda = (unsigned char *)src;
	while (n--)
		*kuda++ = *otkuda++;
	return (dest);
}
