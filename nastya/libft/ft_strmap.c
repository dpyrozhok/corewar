/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:43:59 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/08 21:44:02 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str_new;
	int		i;

	i = 0;
	if (s == 0 || !f)
		return (0);
	str_new = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str_new == NULL)
		return (0);
	while (s[i])
	{
		str_new[i] = f(s[i]);
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}
