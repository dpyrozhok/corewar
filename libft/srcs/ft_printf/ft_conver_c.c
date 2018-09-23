/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:10:30 by popanase          #+#    #+#             */
/*   Updated: 2018/03/19 17:57:31 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

void		ft_handle_flags_c(char c, t_fmt *f)
{
	size_t	i;

	i = 0;
	if (f->fwdth <= 1)
		ft_putchar(c);
	if (f->mns && f->fwdth > 1)
		ft_putchar(c);
	i = f->fwdth;
	while (f->fwdth > 1 && i != 1)
	{
		if (f->zrs && !f->mns)
			ft_putchar('0');
		else
			ft_putchar(' ');
		i--;
	}
	if (!f->mns && f->fwdth > 1)
		ft_putchar(c);
	f->ret = 1;
	if (f->fwdth > 1)
		f->ret = f->fwdth;
}

void		ft_conver_c(va_list ap, t_fmt *f)
{
	char	c;

	c = va_arg(ap, unsigned int);
	ft_handle_flags_c(c, f);
}
