/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:56:51 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:43:00 by popanase         ###   ########.fr       */
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

void				ft_putnbr_fd(int n, int fd)
{
	long int	del;
	int			tmp;

	tmp = n;
	del = ft_getlen(tmp);
	if (tmp == 0)
		ft_putchar_fd(48, fd);
	if (tmp < 0)
	{
		ft_putchar_fd('-', fd);
		tmp *= -1;
	}
	while (del != 1)
	{
		del /= 10;
		if (tmp < 0)
			ft_putchar_fd(48 - tmp / del, fd);
		else
			ft_putchar_fd(48 + tmp / del, fd);
		tmp %= del;
	}
}
