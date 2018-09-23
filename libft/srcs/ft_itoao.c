/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoao.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 18:34:43 by popanase          #+#    #+#             */
/*   Updated: 2018/02/19 18:47:14 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_getleno(size_t n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 8;
		len++;
	}
	return (len);
}

char	*ft_itoao(size_t n)
{
	int		len;
	char	*str;

	len = ft_getleno(n);
	if (!(str = ft_strnew(len + 1)))
		return (NULL);
	str[0] = '0';
	while (len--)
	{
		str[len] = 48 + n % 8;
		n /= 8;
	}
	return (str);
}
