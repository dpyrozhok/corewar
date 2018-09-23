/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 16:19:36 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/11 16:19:38 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*s;
	int		i;

	i = 0;
	s = (char*)malloc(sizeof(char) * size + 1);
	if (!s)
		return (0);
	s[size] = '\0';
	while (s[i])
	{
		s[i] = 0;
		i++;
	}
	return (s);
}
