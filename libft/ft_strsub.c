/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 18:18:11 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:29:06 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (s)
	{
		if ((sub = ft_strnew(len)))
		{
			while (len--)
			{
				sub[i] = s[start];
				i++;
				start++;
			}
			return (sub);
		}
	}
	return (NULL);
}
