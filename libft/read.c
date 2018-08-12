/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:45:52 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/05/10 18:45:53 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_flag(char c, t_lst *option)
{
	if (c == '+')
		option->znak = '+';
	else if (c == ' ' && option->znak != '+')
		option->znak = ' ';
	else if (c == '-')
	{
		option->nul = 'n';
		option->vyravn = 'l';
	}
	else if (c == '0' && option->vyravn != 'l')
		option->nul = 'y';
	else if (c == '#')
		option->h = 'y';
}

char	*ft_precision(char *str, t_lst *option)
{
	char				*precis;
	char				*ptr;

	precis = (char *)malloc(sizeof(char) * (ft_strlen(str)));
	++str;
	ptr = precis;
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		*precis = *str;
		++str;
		++precis;
	}
	*precis = '\0';
	option->tochn_bool = 'y';
	option->precis = ft_atoi(ptr);
	free(ptr);
	return (str);
}

char	*ft_width(char *str, t_lst *option)
{
	char				*width;
	char				*ptr;

	width = (char *)malloc(sizeof(char) * (ft_strlen(str)));
	ptr = width;
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		*width = *str;
		++str;
		++width;
	}
	*width = '\0';
	option->width = ft_atoi(ptr);
	free(ptr);
	return (str);
}

char	*ft_modific_2(char *str, t_lst *option)
{
	if (*(str + 1) != '\0' && *(str + 1) == 'l' && (*str++))
	{
		if (option->modif < '4')
			option->modif = '4';
	}
	else if (option->modif < '3')
		option->modif = '3';
	return (str);
}

char	*ft_modific(char *str, t_lst *option)
{
	while (*str && (*str == 'h' || *str == 'l' || *str == 'z' || *str == 'j'))
	{
		if (*str == 'h')
		{
			if (*(str + 1) != '\0' && *(str + 1) == 'h')
			{
				++str;
				if (option->modif < '1')
					option->modif = '1';
			}
			else if (option->modif < '2')
				option->modif = '2';
		}
		else if (*str == 'l')
			str = ft_modific_2(str, option);
		else if (*str == 'j' && option->modif != '6')
			option->modif = '5';
		else if (*str == 'z')
			option->modif = '6';
		++str;
	}
	return (str);
}
