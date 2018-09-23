/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 16:47:24 by popanase          #+#    #+#             */
/*   Updated: 2018/02/20 16:47:25 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

static void		ft_handle_shrp_x(t_fmt *f)
{
	if (f->shrp && !((f->s[0] == '0' && !f->s[1]) || !f->s[0]))
	{
		ft_strexp_b(f, f->cnv, 1);
		ft_strexp_b(f, '0', 1);
	}
}

static void		ft_handle_flags_x(t_fmt *f)
{
	if (f->prcs && f->s[0] == '0')
		f->s[0] = '\0';
	if (f->prcs && f->prcs_v > ft_strlen(f->s))
		ft_strexp_b(f, '0', f->prcs_v - ft_strlen(f->s));
	if (f->fwdth > ft_strlen(f->s) && f->fwdth > f->prcs_v)
	{
		if (!(!f->mns && f->zrs))
			ft_handle_shrp_x(f);
		if (f->mns)
			ft_strexp_e(f, ' ', f->fwdth - ft_strlen(f->s));
		else if (!f->mns && f->zrs && !f->shrp)
			ft_strexp_b(f, '0', f->fwdth - ft_strlen(f->s));
		else if (!f->mns && f->zrs)
		{
			ft_strexp_b(f, '0', f->fwdth - ft_strlen(f->s) - 2);
			ft_handle_shrp_x(f);
		}
		else
			ft_strexp_b(f, ' ', f->fwdth - ft_strlen(f->s));
	}
	else
		ft_handle_shrp_x(f);
	ft_putstr(f->s);
	f->ret = ft_strlen(f->s);
}

void			ft_conver_x(va_list ap, t_fmt *f)
{
	if (f->md == 1)
		f->s = ft_itoax((unsigned char)va_arg(ap, unsigned int), f->cnv);
	else if (f->md == 2)
		f->s = ft_itoax((unsigned short)va_arg(ap, unsigned int), f->cnv);
	else if (f->md == 4)
		f->s = ft_itoax(va_arg(ap, unsigned long long), f->cnv);
	else if (f->md == 3)
		f->s = ft_itoax(va_arg(ap, unsigned long), f->cnv);
	else if (f->md == 5)
		f->s = ft_itoax(va_arg(ap, uintmax_t), f->cnv);
	else if (f->md == 6)
		f->s = ft_itoax(va_arg(ap, size_t), f->cnv);
	else
		f->s = ft_itoax(va_arg(ap, unsigned int), f->cnv);
	ft_handle_flags_x(f);
}
