/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:24:02 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/09 16:24:03 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	char	*p;
	int		size;

	if (!s1 || !s2)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2);
	new_string = (char*)malloc(sizeof(char) * (size + 1));
	if (!new_string)
		return (0);
	p = new_string;
	while (*s1)
	{
		*new_string = *s1;
		s1++;
		new_string++;
	}
	while (*s2)
	{
		*new_string = *s2;
		s2++;
		new_string++;
	}
	*new_string = '\0';
	return (p);
}
