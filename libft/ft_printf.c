/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:43:56 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/05/10 18:44:01 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	creat_lst(t_lst *opt)
{
	opt->precis = -1;
	opt->vyravn = 'n';
	opt->znak = 'n';
	opt->modif = '0';
	opt->nul = 'n';
	opt->h = 'n';
	opt->tochn_bool = 'n';
	opt->width = 0;
	opt->type = 'n';
}

char	is_param(char *c)
{
	if (*c == '.' && *(c + 1) && (*(c + 1) >= '0' && *(c + 1) <= '9'))
		return ('p');
	if (*c == '.' && *(c + 1) && !(*(c + 1) >= '0' && *(c + 1) <= '9'))
		return ('g');
	if (*c == '-' || *c == '+' || *c == '0' || *c == ' ' || *c == '#')
		return ('f');
	if (*c >= '1' && *c <= '9')
		return ('w');
	if (*c == 'h' || *c == 'l' || *c == 'j' || *c == 'z')
		return ('m');
	if (*c == 'i' || *c == 'd' || *c == 'D' || *c == 'o' || *c == 'O' ||
			*c == 'x' || *c == 'X' || *c == 'c' || *c == 'C' || *c == 'p' ||
			*c == 'u' || *c == 'U' || *c == 's' || *c == 'S')
		return ('t');
	return ('0');
}

int		ft_som_els(char **str, t_lst *option, int *n)
{
	char	*m;

	if (**str == '%')
	{
		if (option->precis == 0)
			option->precis = 1;
		ft_pstr("%", *option, n, 's');
		(*str)++;
	}
	else if (option->width != 0)
	{
		m = malloc(sizeof(char) * 2);
		m[0] = **str;
		m[1] = '\0';
		if (option->precis == 0)
			option->precis = 1;
		ft_pstr(m, *option, n, 's');
		(*str)++;
		free(m);
	}
	return (1);
}

char	*ft_check(char *str, t_lst *option, va_list args, int *n)
{
	while (*str != '\0')
	{
		if (is_param(str) == '0' && ft_som_els(&str, option, n))
			return (str);
		else if (is_param(str) == 'f')
			ft_flag((*str++), option);
		else if (is_param(str) == 'w')
			str = ft_width(str, option);
		else if (is_param(str) == 'm')
			str = ft_modific(str, option);
		else if (is_param(str) == 'p')
			str = ft_precision(str, option);
		else if (is_param(str) == 't')
		{
			ft_type(*str, option, args, n);
			return (++str);
		}
		else if (is_param(str++) == 'g')
			ft_precision("0", option);
	}
	return (NULL);
}

int		ft_printf(char *str, ...)
{
	va_list	args;
	char	*ptr;
	t_lst	option;
	int		n;

	n = 0;
	va_start(args, str);
	while (str && *str != '\0')
	{
		while (*str != '\0' && *str != '%' && ++n)
			ft_putchar((*str++));
		if (*str != '\0' && (*str++) == '%')
		{
			creat_lst(&option);
			ptr = ft_check(str, &option, args, &n);
			str = ptr;
		}
	}
	va_end(args);
	return (n);
}
