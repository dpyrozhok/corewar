/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:40:16 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/09 20:40:17 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_r(long long int n)
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

static int		ft_ma(int roz)
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

void			ft_putnbr_fd(int n, int fd)
{
	int				roz;
	int				mask;
	long long int	new_n;

	new_n = n;
	roz = ft_r(new_n);
	if (new_n < 0)
	{
		ft_putchar_fd('-', fd);
		new_n *= -1;
		roz--;
	}
	mask = ft_ma(roz);
	while (mask > 0)
	{
		ft_putchar_fd(new_n / mask + 48, fd);
		new_n = new_n % mask;
		mask /= 10;
	}
}
