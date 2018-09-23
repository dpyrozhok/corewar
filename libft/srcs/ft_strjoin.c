/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 18:26:06 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:29:16 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 && s2)
	{
		if ((join = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		{
			while (s1[i] != '\0')
			{
				join[i] = s1[i];
				i++;
			}
			while (s2[j] != '\0')
			{
				join[i] = s2[j];
				i++;
				j++;
			}
			return (join);
		}
	}
	return (NULL);
}
