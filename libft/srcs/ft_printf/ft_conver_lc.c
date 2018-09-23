/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_lc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:51:27 by popanase          #+#    #+#             */
/*   Updated: 2018/08/17 10:18:05 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

void	ft_conver_lc(va_list ap, t_fmt *f)
{
	wchar_t	c;

	c = va_arg(ap, int);
	if (MB_CUR_MAX == 1 && ft_count_bits(c) > 8)
		f->ret = -1;
	else if (MB_CUR_MAX == 1 && ft_count_bits(c) <= 8)
		ft_handle_flags_c(c, f);
	else
	{
		if (f->fwdth <= 1)
			f->ret = ft_putwchar(c);
		if (f->mns && f->fwdth > 1)
			f->ret = ft_putwchar(c);
		while (f->fwdth > 1 && f->fwdth > ft_wclen(c)
			&& f->ret != (int)f->fwdth)
		{
			if (f->zrs && !f->mns)
				ft_putchar('0');
			else
				ft_putchar(' ');
			f->ret++;
		}
		if (!f->mns && f->fwdth > 1)
			f->ret += ft_putwchar(c);
	}
}

void	ft_unicode_mask(int *c, wchar_t lc)
{
	int	b;

	b = ft_count_bits(lc);
	if (b <= 7)
		c[0] = lc;
	else if (b <= 11)
	{
		c[0] = (lc >> 6) | 192;
		c[1] = (lc & 63) | 128;
	}
	else if (b <= 16)
	{
		c[0] = (lc >> 12) | 224;
		c[1] = (lc >> 6 & 63) | 128;
		c[2] = (lc & 63) | 128;
	}
	else
	{
		c[0] = (lc >> 18) | 240;
		c[1] = (lc >> 12 & 63) | 128;
		c[2] = (lc >> 6 & 63) | 128;
		c[3] = (lc & 63) | 128;
	}
}

size_t	ft_putwchar(wchar_t lc)
{
	int c[4];
	int	i;
	int	j;

	ft_unicode_mask(c, lc);
	i = 0;
	j = ft_wclen(lc);
	while (i < j)
		write(1, &c[i++], 1);
	return (i);
}
