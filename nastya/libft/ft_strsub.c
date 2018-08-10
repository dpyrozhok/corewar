/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:14:50 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/09 16:14:52 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	char	*p;

	if (!s)
		return (0);
	new_str = (char*)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (0);
	s += start;
	p = new_str;
	while (len)
	{
		*new_str = *s;
		new_str++;
		s++;
		len--;
	}
	*new_str = '\0';
	return (p);
}
