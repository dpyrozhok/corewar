/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:50:14 by popanase          #+#    #+#             */
/*   Updated: 2018/03/05 18:30:20 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

void		ft_handle_flags_s(t_fmt *f)
{
	if (f->prcs && f->prcs_v < ft_strlen(f->s))
		f->s[f->prcs_v] = '\0';
	if (f->fwdth > ft_strlen(f->s) && f->mns)
		ft_strexp_e(f, ' ', f->fwdth - ft_strlen(f->s));
	else if (f->fwdth > ft_strlen(f->s) && f->zrs)
		ft_strexp_b(f, '0', f->fwdth - ft_strlen(f->s));
	else if (f->fwdth > ft_strlen(f->s))
		ft_strexp_b(f, ' ', f->fwdth - ft_strlen(f->s));
	ft_putstr(f->s);
	f->ret = ft_strlen(f->s);
}

void		ft_conver_s(va_list ap, t_fmt *f)
{
	f->s = va_arg(ap, char *);
	if (!f->s)
	{
		f->s = ft_strnew(6);
		ft_strcpy(f->s, "(null)");
	}
	else
		f->s = ft_strdup(f->s);
	ft_handle_flags_s(f);
}
