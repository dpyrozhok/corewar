/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 14:01:21 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/04 19:15:36 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int					i;
	unsigned char		*s;
	unsigned char		*d;

	i = 0;
	s = (unsigned char*)src;
	d = (unsigned char*)dst;
	while (n--)
	{
		d[i] = s[i];
		if (s[i] == (unsigned char)c)
		{
			d[i] = s[i];
			return ((d + 1 + i));
		}
		i++;
	}
	return (NULL);
}
