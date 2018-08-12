/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 20:26:11 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/13 20:26:13 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countspaces(int len, char const *s)
{
	int		start;

	start = 0;
	len--;
	while (s[len] == ' ' || s[len] == '\n' || s[len] == '\t')
	{
		if (len == start)
			return (0);
		len--;
	}
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	return (len - start);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	char	*str;
	int		newlen;
	int		len;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	newlen = ft_countspaces(len, s);
	str = ft_strnew(newlen + 1);
	if (!str)
		return (NULL);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	while (newlen >= i)
	{
		str[i] = *s++;
		i++;
	}
	return (str);
}
