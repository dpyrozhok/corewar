/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:34:11 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:15:25 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *hstck, const char *ndl, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (hstck[i] != '\0' && i < len)
	{
		while (hstck[i] == ndl[j] && i < len)
		{
			if (ndl[j + 1] == '\0')
				return ((char *)(hstck + i - j));
			i++;
			j++;
		}
		i -= j;
		j = 0;
		i++;
	}
	if (ndl[j] == '\0')
		return ((char *)hstck);
	return (NULL);
}
