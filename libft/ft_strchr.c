/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:53:50 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/07 17:54:13 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	char	*g;

	g = (char *)s;
	while (*g)
	{
		if (*g == (char)c)
			return (g);
		g++;
	}
	if ((char)c == '\0')
		return (g);
	return (NULL);
}
