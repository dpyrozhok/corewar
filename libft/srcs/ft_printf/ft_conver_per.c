/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_per.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:38:53 by popanase          #+#    #+#             */
/*   Updated: 2018/02/26 17:39:01 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

void	ft_conver_per(t_fmt *f)
{
	size_t	i;

	i = 0;
	if (f->fwdth <= 1)
		ft_putchar('%');
	if (f->mns && f->fwdth > 1)
		ft_putchar('%');
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
		ft_putchar('%');
	f->ret = 1;
	if (f->fwdth > 1)
		f->ret = f->fwdth;
}
