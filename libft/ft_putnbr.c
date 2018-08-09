/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:03:31 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:42:25 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_getlen(long int tmp)
{
	long int	del;

	del = 1;
	while (tmp)
	{
		tmp /= 10;
		del *= 10;
	}
	return (del);
}

void				ft_putnbr(int n)
{
	long int	del;
	int			tmp;

	tmp = n;
	del = ft_getlen(tmp);
	if (tmp == 0)
		ft_putchar(48);
	if (tmp < 0)
	{
		ft_putchar('-');
		tmp *= -1;
	}
	while (del != 1)
	{
		del /= 10;
		if (tmp < 0)
			ft_putchar(48 - tmp / del);
		else
			ft_putchar(48 + tmp / del);
		tmp %= del;
	}
}
