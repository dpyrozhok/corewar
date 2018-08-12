/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:54:45 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/08 19:54:48 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_waja(const char *big, const char *little, int b,
	int metka)
{
	if (metka && little[b] == '\0')
		return ((char*)big + metka - b);
	return (0);
}

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	int			b;
	int			metka;

	i = 0;
	b = 0;
	metka = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && little[b] && i < len)
	{
		if (big[i] == little[b] && i < len)
		{
			metka = i + 1;
			b += 1;
		}
		else
		{
			metka = 0;
			i -= b;
			b = 0;
		}
		i++;
	}
	return (ft_waja(big, little, b, metka));
}
