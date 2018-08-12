/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 22:41:24 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/22 22:41:26 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		*ft_asort(int *a, size_t n)
{
	size_t	i;
	size_t	j;
	int		tmp;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (a[j] > a[j + 1])
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (a);
}

static int		*ft_dsort(int *a, size_t n)
{
	size_t	i;
	size_t	j;
	int		tmp;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (a[j] < a[j + 1])
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (a);
}

int				*ft_intsort(int *a, size_t n, char order)
{
	if (order == 'a')
		return (ft_asort(a, n));
	if (order == 'd')
		return (ft_dsort(a, n));
	return (0);
}
