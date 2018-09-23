/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_lc_ls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:27:18 by popanase          #+#    #+#             */
/*   Updated: 2018/03/19 17:56:35 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

size_t			ft_wclen(wchar_t lc)
{
	int	b;

	b = ft_count_bits(lc);
	if (b <= 7)
		return (1);
	else if (b <= 11)
		return (2);
	else if (b <= 16)
		return (3);
	else
		return (4);
}

int				ft_count_bits(wchar_t lc)
{
	int	i;

	i = 0;
	while (lc)
	{
		lc = lc >> 1;
		i++;
	}
	return (i);
}

int				ft_check_type(wchar_t *ls)
{
	wchar_t	*t;

	t = ls;
	while (*t)
	{
		if (ft_count_bits(*t) > 8)
			return (0);
		t++;
	}
	return (1);
}

size_t			ft_wstrlen(wchar_t *ls)
{
	int	i;
	int	ret;
	int	b;

	i = 0;
	ret = 0;
	while (ls[i])
	{
		b = ft_count_bits(ls[i]);
		if (b <= 7)
			ret++;
		else if (b <= 11)
			ret += 2;
		else if (b <= 16)
			ret += 3;
		else
			ret += 4;
		i++;
	}
	return (ret);
}

size_t			ft_getwdth(wchar_t *ls, t_fmt *f)
{
	size_t		ret;
	size_t		len;
	wchar_t		*tmp;

	len = 0;
	ret = 0;
	tmp = ls;
	if (!f->prcs || f->mns || f->prcs_v >= ft_wstrlen(ls))
		len = f->fwdth - ft_wstrlen(ls);
	else if (f->fwdth > f->prcs_v)
	{
		len = f->fwdth - f->prcs_v;
		while (ret + ft_wclen(*ls) <= f->prcs_v && *tmp)
		{
			ret += ft_wclen(*tmp);
			tmp++;
		}
		len = len + (f->prcs_v - ret);
	}
	return (len);
}
