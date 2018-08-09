/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 17:29:41 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:28:24 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
			fresh[i] = f(s[i]);
			i++;
		}
		return (fresh);
	}
	return (NULL);
}
