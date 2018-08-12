/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:55:04 by amalkevy          #+#    #+#             */
/*   Updated: 2017/10/30 19:44:19 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = dest;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (dest);
}
