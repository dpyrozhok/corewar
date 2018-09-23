/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:49:18 by popanase          #+#    #+#             */
/*   Updated: 2018/03/05 18:31:17 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

static size_t	ft_handle_flags_p(t_fmt *f)
{
	if (f->prcs && f->s[0] == '0')
		f->s[0] = '\0';
	if (f->prcs && f->prcs_v > ft_strlen(f->s) && !ft_strchr(f->s, '-'))
		ft_strexp_b(f, '0', f->prcs_v - ft_strlen(f->s));
	ft_strexp_b(f, 'x', 1);
	ft_strexp_b(f, '0', 1);
	if (f->fwdth > ft_strlen(f->s) && f->mns)
		ft_strexp_e(f, ' ', f->fwdth - ft_strlen(f->s));
	else if (f->fwdth > ft_strlen(f->s) && f->zrs)
		ft_strexp_e(f, '0', f->fwdth - ft_strlen(f->s));
	else if (f->fwdth > ft_strlen(f->s))
		ft_strexp_b(f, ' ', f->fwdth - ft_strlen(f->s));
	ft_putstr(f->s);
	return (ft_strlen(f->s));
}

void			ft_conver_p(va_list ap, t_fmt *f)
{
	f->s = ft_itoax(va_arg(ap, size_t), f->cnv);
	f->ret = ft_handle_flags_p(f);
}
