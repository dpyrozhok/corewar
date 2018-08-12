/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:36:07 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/02 19:54:53 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	a;

	i = 0;
	a = (char)c;
	if (a == '\0')
	{
		while (s[i])
			i++;
		return ((char*)(s + i));
	}
	while (s[i])
	{
		if (s[i] == a)
			return ((char *)(&s[i]));
		i++;
	}
	return (0);
}
