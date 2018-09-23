/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_ls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:50:14 by popanase          #+#    #+#             */
/*   Updated: 2018/03/19 17:57:54 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

static size_t		ft_putwstr(wchar_t *ls, t_fmt *f)
{
	size_t	ret;
	size_t	len;

	ret = 0;
	len = ft_wstrlen(ls);
	while (*ls)
	{
		if (f->prcs && f->prcs_v < len && ret + ft_wclen(*ls) > f->prcs_v)
			return (ret);
		ret += ft_putwchar(*ls);
		ls++;
	}
	return (ret);
}

static void			ft_handle_flags_ls(wchar_t *ls, t_fmt *f)
{
	size_t	len;

	len = ft_getwdth(ls, f);
	if (f->mns)
		f->ret += ft_putwstr(ls, f);
	if ((f->fwdth > ft_wstrlen(ls) || (f->prcs && f->fwdth > f->prcs_v)))
	{
		while (len)
		{
			if (f->zrs)
				ft_putchar('0');
			else
				ft_putchar(' ');
			len--;
			f->ret++;
		}
	}
	if (!f->mns)
		f->ret += ft_putwstr(ls, f);
}

void				ft_conver_ls(va_list ap, t_fmt *f)
{
	wchar_t	*ls;
	char	*s;

	ls = va_arg(ap, wchar_t *);
	if (MB_CUR_MAX == 1 && !ft_check_type(ls))
		f->ret = -1;
	else if (MB_CUR_MAX == 1 && !ft_check_type(ls))
	{
		f->s = (char *)ls;
		ft_handle_flags_s(f);
	}
	else
	{
		if (!ls)
		{
			s = ft_strnew(6);
			ft_strcpy(s, "(null)");
			if (f->prcs && f->prcs_v < ft_strlen(s))
				s[f->prcs_v] = '\0';
			ft_putstr(s);
			f->ret = ft_strlen(s);
		}
		else
			ft_handle_flags_ls(ls, f);
	}
}
