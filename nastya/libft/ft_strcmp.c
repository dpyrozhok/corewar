/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 21:00:59 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/03 15:01:40 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*a;
	unsigned char	*b;
	int				i;

	i = 0;
	a = (unsigned char*)s1;
	b = (unsigned char*)s2;
	while (a[i] == b[i] && b[i])
		i++;
	if (b[i] == '\0' && a[i] == '\0')
		return (0);
	else
		return (a[i] - b[i]);
}
