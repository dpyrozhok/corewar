/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:46:58 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/15 15:46:59 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int		i;
	int		b;

	i = 0;
	b = n;
	if (b == 0)
		return (1);
	if (b < 0)
	{
		b *= -1;
		i++;
	}
	while (b > 0)
	{
		b = b / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_len(n);
	s = ft_strnew(len);
	len--;
	if (n < 0 && s)
	{
		n *= -1;
		s[0] = '-';
	}
	while (len >= 0 && s)
	{
		i = n % 10;
		n = n / 10;
		s[len] = i + '0';
		if (len == 1 && s[0] == '-')
			return (s);
		len--;
	}
	return (s);
}
