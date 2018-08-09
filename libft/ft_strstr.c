/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:00:01 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:14:16 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strstr(const char *hstck, const char *ndl)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (hstck[i] != '\0')
	{
		while (hstck[i] == ndl[j])
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
