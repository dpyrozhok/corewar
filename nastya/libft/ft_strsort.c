/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:22:02 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/15 17:22:04 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsort(char **s)
{
	int		i;
	int		j;
	int		l;
	char	*tmp;

	l = ft_countw(s);
	i = 0;
	while (i < ft_countw(s))
	{
		j = 0;
		while (j < l - i - 1)
		{
			if (ft_strcmp(s[j], s[j + 1]) > 0)
			{
				tmp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (s);
}
