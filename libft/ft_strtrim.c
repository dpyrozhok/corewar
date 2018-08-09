/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 18:47:56 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:29:31 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_getend(const char *s)
{
	size_t i;

	i = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i--;
	return (i + 1);
}

char			*ft_strtrim(char const *s)
{
	char	*trim;
	size_t	i;
	size_t	j;
	size_t	end;

	i = 0;
	j = 0;
	if (s)
	{
		while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
			i++;
		end = ft_getend(s);
		if (end > i)
			trim = ft_strnew(end - i);
		else
			trim = ft_strnew(0);
		if (trim)
		{
			while (i < end)
				trim[j++] = s[i++];
			return (trim);
		}
	}
	return (NULL);
}
