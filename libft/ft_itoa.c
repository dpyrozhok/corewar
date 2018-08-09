/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 17:54:56 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:30:59 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_getlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	unsigned int	len;
	char			*str;

	len = ft_getlen(n);
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len--)
	{
		if (n < 0)
		{
			str[len] = 48 - n % 10;
			if (len == 1)
			{
				len--;
				str[0] = '-';
			}
		}
		else
			str[len] = 48 + n % 10;
		n /= 10;
	}
	return (str);
}
