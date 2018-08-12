/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 13:48:12 by amalkevy          #+#    #+#             */
/*   Updated: 2017/10/31 18:06:03 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	const unsigned char	*s;
	unsigned char		*d;

	i = 0;
	s = src;
	d = dst;
	if (!src && !dst)
		return (0);
	if (dst >= src)
	{
		while (len--)
			d[len] = s[len];
	}
	else
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	return (dst);
}
