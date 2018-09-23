/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_inv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:00:56 by popanase          #+#    #+#             */
/*   Updated: 2018/03/14 19:00:59 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

void	ft_conver_inv(t_fmt *format)
{
	size_t	ret;

	ret = 0;
	if (format->cnv && format->mns)
		ft_putchar(format->cnv);
	if (format->fwdth > 0)
		format->fwdth--;
	while (ret != format->fwdth)
	{
		if (format->zrs)
			ft_putchar('0');
		else
			ft_putchar(' ');
		ret++;
	}
	if (format->cnv && !format->mns)
		ft_putchar(format->cnv);
	if (format->cnv)
		ret++;
	format->ret = ret;
}
