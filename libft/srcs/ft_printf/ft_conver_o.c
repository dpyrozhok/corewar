/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_o.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 17:51:49 by popanase          #+#    #+#             */
/*   Updated: 2018/02/20 17:51:52 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

static void		ft_handle_shrp_o(t_fmt *f)
{
	if (f->shrp && f->s[0] != '0')
		ft_strexp_b(f, '0', 1);
}

static void		ft_handle_flags_o(t_fmt *f)
{
	if (f->prcs && f->s[0] == '0' && !f->s[1])
		f->s[0] = '\0';
	if (f->prcs && f->prcs_v > ft_strlen(f->s))
		ft_strexp_b(f, '0', f->prcs_v - ft_strlen(f->s));
	if (f->fwdth > ft_strlen(f->s) && f->fwdth > f->prcs_v)
	{
		if (!(!f->mns && f->zrs))
			ft_handle_shrp_o(f);
		if (f->mns)
			ft_strexp_e(f, ' ', f->fwdth - ft_strlen(f->s));
		else if (!f->mns && f->zrs && !f->shrp)
			ft_strexp_b(f, '0', f->fwdth - ft_strlen(f->s));
		else if (!f->mns && f->zrs)
		{
			ft_strexp_b(f, '0', f->fwdth - ft_strlen(f->s) - 2);
			ft_handle_shrp_o(f);
		}
		else
			ft_strexp_b(f, ' ', f->fwdth - ft_strlen(f->s));
	}
	else
		ft_handle_shrp_o(f);
	ft_putstr(f->s);
	f->ret = ft_strlen(f->s);
}

void			ft_conver_o(va_list ap, t_fmt *f)
{
	if (f->md == 1 && f->cnv != 'O')
		f->s = ft_itoao((unsigned char)va_arg(ap, unsigned int));
	else if (f->md == 2 && f->cnv != 'O')
		f->s = ft_itoao((unsigned short)va_arg(ap, unsigned int));
	else if (f->md == 4)
		f->s = ft_itoao(va_arg(ap, unsigned long long));
	else if (f->md == 3 || f->cnv == 'O')
		f->s = ft_itoao(va_arg(ap, unsigned long));
	else if (f->md == 5)
		f->s = ft_itoao(va_arg(ap, uintmax_t));
	else if (f->md == 6)
		f->s = ft_itoao(va_arg(ap, size_t));
	else
		f->s = ft_itoao(va_arg(ap, unsigned int));
	ft_handle_flags_o(f);
}
