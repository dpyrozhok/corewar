/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:27:36 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:04:14 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char		*buf_s;
	char			*buf_d;

	buf_s = (const char *)src;
	buf_d = (char *)dst;
	while (n--)
		*(buf_d + n) = *(buf_s + n);
	return (dst);
}
