/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 18:22:41 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:18:45 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*buf_s1;
	unsigned char	*buf_s2;
	size_t			i;

	i = 0;
	buf_s1 = (unsigned char *)s1;
	buf_s2 = (unsigned char *)s2;
	while (buf_s1[i])
	{
		if (buf_s1[i] != buf_s2[i])
			return (buf_s1[i] - buf_s2[i]);
		i++;
	}
	return (buf_s1[i] - buf_s2[i]);
}
