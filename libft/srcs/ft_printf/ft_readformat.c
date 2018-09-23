/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readformat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:58:04 by popanase          #+#    #+#             */
/*   Updated: 2018/03/14 18:58:25 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

int		ft_free_format(t_fmt *format)
{
	if (format->s)
		free(format->s);
	free(format);
	return (1);
}

int		ft_skip(char c)
{
	if (c == 'h' || c == 'l' || c == 'z' ||
		c == 'j' || c == ' ' || c == '#' || c == '+' || c == '-' || c == '.' ||
		(c >= '0' && c <= '9'))
		return (1);
	return (0);
}

void	ft_read_md(const char *f, t_fmt *format)
{
	if (*f == 'h' && format->md == 2)
		format->md = 1;
	else if (*f == 'h' && format->md != 2 && format->md < 2)
		format->md = 2;
	if (*f == 'l' && format->md != 3 && format->md < 3)
		format->md = 3;
	else if (*f == 'l' && format->md == 3 && format->md < 4)
		format->md = 4;
	if (*f == 'j' && format->md < 5)
		format->md = 5;
	if (*f == 'z')
		format->md = 6;
}

void	ft_read_flags(char c, t_fmt *format)
{
	if (c == '#')
		format->shrp = 1;
	if (c == '0')
		format->zrs = 1;
	if (c == ' ')
		format->spc = 1;
	if (c == '-')
		format->mns = 1;
	if (c == '+')
		format->pls = 1;
}

void	ft_read_format(const char *f, t_fmt *format)
{
	while (ft_skip(*f) && *f)
	{
		ft_read_flags(*f, format);
		if (ft_isdigit(*f) && !format->fwdth)
		{
			format->fwdth = ft_atoi(f);
			while (ft_isdigit(*f))
				f++;
			f--;
		}
		if (*f == '.')
		{
			format->prcs = 1;
			format->prcs_v = ft_atoi(f + 1);
			while (ft_isdigit(*(f + 1)))
				f++;
		}
		ft_read_md(f, format);
		f++;
	}
	format->cnv = *f;
}
