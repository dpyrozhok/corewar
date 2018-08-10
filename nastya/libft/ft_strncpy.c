/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:16:20 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/06 20:22:50 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	int		m;

	m = 0;
	i = 0;
	if (ft_strlen(src) < len)
		while (i < len)
		{
			if (src[i] == '\0' || m == 1)
			{
				dst[i] = 0;
				m = 1;
			}
			else
				dst[i] = src[i];
			i++;
		}
	else
		while (i < len)
		{
			dst[i] = src[i];
			i++;
		}
	return (dst);
}
