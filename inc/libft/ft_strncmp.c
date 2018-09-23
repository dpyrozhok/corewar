/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:20:31 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/22 19:37:04 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*news1;
	unsigned char	*news2;

	if (n == 0)
		return (0);
	news1 = (unsigned char*)s1;
	news2 = (unsigned char*)s2;
	while (*news1 == *news2 && *news1 != '\0' && *news2 != '\0' && n - 1 > 0)
	{
		news1++;
		news2++;
		n--;
	}
	if (*news1 != *news2)
		return ((int)(*news1 - *news2));
	return (0);
}
