/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:41:34 by popanase          #+#    #+#             */
/*   Updated: 2018/02/26 16:41:53 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

static void		ft_handle_flags_u(t_fmt *f)
{
	if (f->prcs && f->s[0] == '0')
		f->s[0] = '\0';
	if (f->prcs && f->prcs_v > ft_strlen(f->s))
		ft_strexp_b(f, '0', f->prcs_v - ft_strlen(f->s));
	else if (f->prcs && f->prcs_v > ft_strlen(f->s))
		ft_strexp_b(f, '0', f->prcs_v - ft_strlen(f->s) + 1);
	if (f->fwdth > ft_strlen(f->s) && f->fwdth > f->prcs_v)
	{
		if (f->mns)
			ft_strexp_e(f, ' ', f->fwdth - ft_strlen(f->s));
		else if (f->zrs && f->prcs)
			ft_strexp_b(f, '0', f->fwdth - ft_strlen(f->s));
		else if (f->zrs && !f->prcs)
			ft_strexp_b(f, '0', f->fwdth - ft_strlen(f->s));
		else
			ft_strexp_b(f, ' ', f->fwdth - ft_strlen(f->s));
	}
	ft_putstr(f->s);
}

void			ft_conver_u(va_list ap, t_fmt *f)
{
	if (f->md == 1 && f->cnv != 'U')
		f->s = ft_itoau((unsigned char)va_arg(ap, unsigned int));
	else if (f->md == 2 && f->cnv != 'U')
		f->s = ft_itoau((unsigned short)va_arg(ap, unsigned int));
	else if (f->md == 4)
		f->s = ft_itoau(va_arg(ap, unsigned long long));
	else if (f->md == 5)
		f->s = ft_itoau(va_arg(ap, uintmax_t));
	else if (f->md == 6)
		f->s = ft_itoau(va_arg(ap, size_t));
	else if ((f->md == 3) || f->cnv == 'U')
		f->s = ft_itoau(va_arg(ap, unsigned long));
	else
		f->s = ft_itoau(va_arg(ap, unsigned int));
	ft_handle_flags_u(f);
	f->ret = ft_strlen(f->s);
}
