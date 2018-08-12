/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:00:15 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/09 19:00:17 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_roz(long long int n)
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

static int		ft_mask(int roz)
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

static char		*ft_final(long long int n, int mask, char *num)
{
	int		i;

	i = 0;
	if (num[0] == '-')
		i++;
	while (mask > 0)
	{
		num[i] = n / mask + 48;
		n = n % mask;
		mask /= 10;
		i++;
	}
	num[i] = '\0';
	return (num);
}

char			*ft_itoa(int n)
{
	char			*num;
	int				roz;
	int				mask;
	long long int	new_n;

	new_n = n;
	roz = ft_roz(new_n);
	num = ft_strnew(roz);
	if (!num)
		return (0);
	if (new_n < 0)
	{
		num[0] = '-';
		new_n *= -1;
		roz--;
	}
	mask = ft_mask(roz);
	num = ft_final(new_n, mask, num);
	return (num);
}
