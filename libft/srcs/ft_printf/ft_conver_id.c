/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:44:23 by popanase          #+#    #+#             */
/*   Updated: 2018/03/19 17:59:07 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

static void		ft_handle_prcs_id(t_fmt *f)
{
	if (f->prcs && f->prcs_v > ft_strlen(f->s) &&
			!ft_strchr(f->s, '-') && !f->spc)
		ft_strexp_b(f, '0', f->prcs_v - ft_strlen(f->s));
	else if (f->prcs && f->prcs_v > ft_strlen(f->s) &&
			!ft_strchr(f->s, '-') && f->spc)
	{
		ft_strexp_b(f, '0', f->prcs_v - ft_strlen(f->s));
		ft_strexp_b(f, ' ', 1);
	}
	else if (f->prcs && f->prcs_v > ft_strlen(f->s) && ft_strchr(f->s, '-'))
		ft_strexp_b(f, '0', f->prcs_v - ft_strlen(f->s) + 1);
	if (f->prcs && ft_strchr(f->s, '-') && f->s[0] == '0')
	{
		*(ft_strchr(f->s, '-')) = '0';
		f->s[0] = '-';
	}
}

static void		ft_handle_pls(t_fmt *f)
{
	if (f->pls && !ft_strchr(f->s, '-'))
		ft_strexp_b(f, '+', 1);
}

static void		ft_handle_width_id(t_fmt *f)
{
	if (!(!f->mns && f->pls && f->zrs))
		ft_handle_pls(f);
	if (f->mns)
		ft_strexp_e(f, ' ', f->fwdth - ft_strlen(f->s));
	else if (f->pls && !ft_strchr(f->s, '-') && f->zrs)
	{
		ft_strexp_b(f, '0', f->fwdth - ft_strlen(f->s) - 1);
		ft_handle_pls(f);
	}
	else if (f->zrs && f->spc && !f->prcs)
	{
		ft_strexp_b(f, '0', f->fwdth - ft_strlen(f->s) - 1);
		ft_strexp_b(f, ' ', 1);
	}
	else if (f->zrs && ((ft_strchr(f->s, '-') && f->prcs) || !f->prcs))
		ft_strexp_b(f, '0', f->fwdth - ft_strlen(f->s));
	else
		ft_strexp_b(f, ' ', f->fwdth - ft_strlen(f->s));
}

static void		ft_handle_flags_id(t_fmt *f)
{
	if (f->prcs && f->s[0] == '0')
		f->s[0] = '\0';
	if (f->spc && !f->pls && !f->fwdth && !ft_strchr(f->s, '-') && !f->prcs)
		ft_strexp_b(f, ' ', 1);
	ft_handle_prcs_id(f);
	if (f->fwdth > ft_strlen(f->s) && f->fwdth > f->prcs_v)
	{
		ft_handle_width_id(f);
		if (ft_strchr(f->s, '-') && f->s[0] == '0')
		{
			*(ft_strchr(f->s, '-')) = '0';
			f->s[0] = '-';
		}
	}
	else
		ft_handle_pls(f);
	ft_putstr(f->s);
}

void			ft_conver_id(va_list ap, t_fmt *f)
{
	if (f->md == 1 && f->cnv != 'D')
		f->s = ft_itoal((char)va_arg(ap, int));
	else if (f->md == 2 && f->cnv != 'D')
		f->s = ft_itoal((short)va_arg(ap, int));
	else if (f->md == 4)
		f->s = ft_itoal(va_arg(ap, long long));
	else if (f->md == 3 || f->cnv == 'D')
		f->s = ft_itoal(va_arg(ap, long));
	else if (f->md == 5)
		f->s = ft_itoal(va_arg(ap, intmax_t));
	else if (f->md == 6)
		f->s = ft_itoal(va_arg(ap, size_t));
	else
		f->s = ft_itoal(va_arg(ap, int));
	ft_handle_flags_id(f);
	f->ret = ft_strlen(f->s);
}
