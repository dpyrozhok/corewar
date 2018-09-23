/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:47:54 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/08 20:47:56 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*news1;
	unsigned char	*news2;

	news1 = (unsigned char*)s1;
	news2 = (unsigned char*)s2;
	while (*news1 == *news2 && *news1 != '\0' && *news2 != '\0')
	{
		news1++;
		news2++;
	}
	if (*news1 != *news2)
		return ((int)(*news1 - *news2));
	return (0);
}
