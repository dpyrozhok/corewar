/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 16:55:48 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 18:06:19 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*buf_s;
	char		buf_c;

	buf_s = (const char*)s;
	buf_c = (char)c;
	while (n--)
	{
		if (*(buf_s++) == buf_c)
			return ((void*)(buf_s - 1));
	}
	return (NULL);
}
