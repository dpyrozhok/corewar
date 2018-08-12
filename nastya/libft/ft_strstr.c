/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 20:28:43 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/10 13:13:47 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check(const char *haystack, const char *needle, int *j)
{
	int		i;
	int		posit;

	i = 0;
	posit = 0;
	while (haystack && haystack[i] && needle[*j])
	{
		if (haystack[i] == needle[*j])
		{
			posit = i + 1;
			*j = *j + 1;
		}
		else
		{
			posit = 0;
			i -= *j;
			*j = 0;
		}
		i++;
	}
	return (posit);
}

char			*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		posit;
	int		*a;

	i = 0;
	j = 0;
	a = &j;
	if (needle[i] == '\0')
		return ((char*)haystack);
	posit = check(haystack, needle, a);
	if (posit && needle[j] == '\0')
		return ((char*)(haystack + posit - j));
	return (0);
}
