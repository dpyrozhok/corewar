/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 11:41:09 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/04 13:18:13 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int						i;
	unsigned long long int	rs;
	int						z;

	i = 0;
	rs = 0;
	z = 1;
	while (str && ((str[i] == '\t' || str[i] == '\v' || str[i] == '\f') ||
	(str[i] == '\r' || str[i] == '\n' || str[i] == ' ')))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			z = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (i > 24 && z == 1)
			return (-1);
		if (i >= 26 && z == -1)
			return (0);
		rs = rs * 10 + str[i++] - 48;
	}
	return (rs * z);
}
