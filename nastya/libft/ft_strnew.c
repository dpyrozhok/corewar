/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:21:47 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/08 21:22:17 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*s;

	s = (char*)malloc(sizeof(char) * (size + 1));
	if (!s)
		return (0);
	ft_bzero(s, size + 1);
	return (s);
}
