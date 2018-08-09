/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:41:33 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:07:06 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*buf_s1;
	unsigned char	*buf_s2;
	unsigned int	i;

	buf_s1 = (unsigned char*)s1;
	buf_s2 = (unsigned char*)s2;
	i = 0;
	while (n--)
	{
		if (buf_s1[i] != buf_s2[i])
			return (buf_s1[i] - buf_s2[i]);
		i++;
	}
	return (0);
}
