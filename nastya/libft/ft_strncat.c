/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 19:21:11 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/01 19:40:16 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t len)
{
	int		i;
	size_t	j;

	j = 0;
	i = 0;
	while (dst[i])
		i++;
	while (src[j] && j < len)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}
