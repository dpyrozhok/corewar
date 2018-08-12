/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:39:55 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/07 18:39:58 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*g;
	int		i;

	i = 0;
	g = (char *)s;
	while (g[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (g[i] == c)
			return ((char*)s + i);
		i--;
	}
	return (NULL);
}
