/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:58:38 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/10 19:58:41 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int							ft_atoi(const char *str)
{
	int						zn;
	unsigned long long int	res;
	int						count;

	count = 0;
	zn = 1;
	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
		*str == '\v' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			zn = zn * (-1);
	while (*str >= 48 && *str <= 57)
	{
		if (count > 24 && zn == 1)
			return (-1);
		if (count > 17 && zn == -1)
			return (0);
		res = res * 10 + (*str - 48);
		str++;
		count++;
	}
	return (res * zn);
}
