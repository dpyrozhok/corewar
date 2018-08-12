/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:22:37 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/06 18:50:21 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*a;

	i = 0;
	a = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!a)
		return (0);
	while (s1[i])
	{
		a[i] = (char)s1[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}
