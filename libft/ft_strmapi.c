/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:03:11 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/13 16:03:13 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*b;
	char	*c;
	int		len;

	c = (char*)s;
	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(c);
	b = (char*)malloc(sizeof(char) * len + 1);
	if (!b)
		return (NULL);
	if (s)
	{
		while (c[i])
		{
			b[i] = f(i, c[i]);
			i++;
		}
		b[i] = '\0';
		return (b);
	}
	return (NULL);
}
