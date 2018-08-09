/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:52:18 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:19:31 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	size_t	i;
	int		flag;
	size_t	n;

	i = 0;
	flag = 1;
	n = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-' && str[i])
		flag = -1;
	if ((str[i] == '+' || str[i] == '-') && str[i])
		i++;
	while (ft_isdigit(str[i]) && str[i] && n < 9223372036854775807)
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	if (n < 9223372036854775807)
		return (n * flag);
	else if (flag == 1)
		return (-1);
	else
		return (0);
}
