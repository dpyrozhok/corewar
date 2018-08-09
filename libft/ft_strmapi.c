/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 17:35:55 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:28:29 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*fresh;
	size_t	i;

	i = 0;
	if (s && f)
	{
		if (!(fresh = ft_strnew(ft_strlen(s))))
			return (NULL);
		while (i < ft_strlen(s))
		{
			fresh[i] = f(i, s[i]);
			i++;
		}
		return (fresh);
	}
	return (NULL);
}
