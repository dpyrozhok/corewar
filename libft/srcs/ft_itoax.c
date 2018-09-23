/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:55:29 by popanase          #+#    #+#             */
/*   Updated: 2018/03/19 18:21:27 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_getlenx(size_t n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

char	*ft_itoax(size_t n, char c)
{
	int		len;
	char	*str;

	len = ft_getlenx(n);
	if (!(str = ft_strnew(len + 1)))
		return (NULL);
	str[0] = '0';
	while (len--)
	{
		if (n % 16 > 9 && c > 96 && c < 123)
			str[len] = 87 + n % 16;
		else if (n % 16 > 9 && c > 64 && c < 91)
			str[len] = 55 + n % 16;
		else
			str[len] = 48 + n % 16;
		n /= 16;
	}
	return (str);
}
