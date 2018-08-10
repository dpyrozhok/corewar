/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:29:49 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/09 16:29:51 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_stncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	int		m;

	m = 0;
	i = 0;
	if (ft_strlen(src) < len)
		while (i < len)
		{
			if (src[i] == '\0' || m == 1)
			{
				dst[i] = 0;
				m = 1;
			}
			else
				dst[i] = src[i];
			i++;
		}
	else
		while (i < len)
		{
			dst[i] = src[i];
			i++;
		}
	dst[i] = '\0';
	return (dst);
}

char			*ft_strtrim(char const *s)
{
	char		*new_string;
	const char	*p;
	int			l;

	l = 0;
	if (!s)
		return (0);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	p = s;
	while (*++s)
		l++;
	s--;
	while (*s == ' ' || *s == '\n' || *s == '\t')
	{
		l--;
		s--;
	}
	new_string = (char*)malloc(sizeof(char) * (l + 2));
	if (!new_string)
		return (0);
	new_string = ft_stncpy(new_string, p, l + 1);
	return (new_string);
}
