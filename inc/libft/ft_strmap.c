/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 16:46:42 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/11 16:46:43 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
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
			b[i] = f(c[i]);
			i++;
		}
		b[i] = '\0';
		return (b);
	}
	return (NULL);
}
