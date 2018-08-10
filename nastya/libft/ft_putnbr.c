/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:24:13 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/09 20:24:14 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_ro(long long int n)
{
	int		roz;

	roz = 0;
	if (n < 0)
	{
		roz++;
		n *= -1;
	}
	if (n == 0)
		roz = 1;
	while (n > 0)
	{
		n /= 10;
		roz++;
	}
	return (roz);
}

static int		ft_mas(int roz)
{
	int		i;
	int		mask;

	mask = 1;
	i = 1;
	while (i < roz)
	{
		mask *= 10;
		i++;
	}
	return (mask);
}

void			ft_putnbr(int n)
{
	int				roz;
	int				mask;
	long long int	new_n;

	new_n = n;
	roz = ft_ro(new_n);
	if (new_n < 0)
	{
		ft_putchar('-');
		new_n *= -1;
		roz--;
	}
	mask = ft_mas(roz);
	while (mask > 0)
	{
		ft_putchar(new_n / mask + 48);
		new_n = new_n % mask;
		mask /= 10;
	}
}
