/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:55:29 by popanase          #+#    #+#             */
/*   Updated: 2018/02/19 18:29:53 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		ft_getlen(long long int n)
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

char			*ft_itoal(long long int n)
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
