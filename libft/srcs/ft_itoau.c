/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:55:29 by popanase          #+#    #+#             */
/*   Updated: 2018/03/19 18:22:56 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		ft_getlenu(size_t n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoau(size_t n)
{
	int		len;
	char	*str;

	len = ft_getlenu(n);
	if (!(str = ft_strnew(len + 1)))
		return (NULL);
	str[0] = '0';
	while (len--)
	{
		str[len] = 48 + n % 10;
		n /= 10;
	}
	return (str);
}
