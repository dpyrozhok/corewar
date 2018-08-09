/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 19:02:37 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:29:46 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**arr;

	i = 0;
	j = 0;
	k = 0;
	if (!s || !(arr = (char **)malloc(sizeof(char *) * (ft_cntwrd(s, c) + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
			j = ft_lnwrd(s, c, i);
		i += j;
		if ((s[i] == c || s[i] == '\0') && j != 0)
		{
			arr[k++] = ft_strsub(s, i - j, j);
			j = 0;
			i--;
		}
		i++;
	}
	arr[k] = NULL;
	return (arr);
}
