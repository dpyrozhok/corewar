/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:45:24 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/07 14:03:15 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check(const char *haystack, const char *needle,
	int *j, size_t len)
{
	size_t		i;
	int			posit;

	i = 0;
	posit = 0;
	while (haystack[i] && needle[*j] && i < len)
	{
		if (haystack[i] == needle[*j] && i < len)
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

char			*ft_strnstr(const char *haystack,
	const char *needle, size_t len)
{
	int		i;
	int		j;
	int		posit;
	int		*a;

	i = 0;
	j = 0;
	a = &j;
	posit = 0;
	if (needle[i] == '\0')
		return ((char*)haystack);
	posit = check(haystack, needle, a, len);
	if (posit && needle[j] == '\0')
		return ((char*)(haystack + posit - j));
	return (0);
}
