/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 21:30:07 by popanase          #+#    #+#             */
/*   Updated: 2018/09/24 00:45:25 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_put_4(t_core *core, int arg, int pos)
{
	if (pos < 0)
		pos = MEM_SIZE + pos;
	core->arena[pos % MEM_SIZE] = (unsigned char)(arg >> 24);
	core->arena[(pos + 1) % MEM_SIZE] = (unsigned char)(arg >> 16 & 255);
	core->arena[(pos + 2) % MEM_SIZE] = (unsigned char)(arg >> 8 & 255);
	core->arena[(pos + 3) % MEM_SIZE] = (unsigned char)(arg & 255);
}

int		ft_read_1(t_core *core, int pos)
{
	int		ret;

	if (pos < 0)
		pos = MEM_SIZE + pos;
	ret = (int)((unsigned char)core->arena[(pos + 1) % MEM_SIZE]);
	return (ret);
}

int		ft_read_2(t_core *core, int pos)
{
	short	ret;

	if (pos < 0)
		pos = MEM_SIZE + pos;
	ret = (short)(
			core->arena[(pos + 1) % MEM_SIZE] << 8 |
			core->arena[(pos + 2) % MEM_SIZE]);
	return (int)(ret);
}

int		ft_read_4(t_core *core, int pos)
{
	int		ret;

	if (pos < 0)
		pos = MEM_SIZE + pos;
	ret = (int)(
			core->arena[(pos + 1) % MEM_SIZE] << 24 |
			core->arena[(pos + 2) % MEM_SIZE] << 16 |
			core->arena[(pos + 3) % MEM_SIZE] << 8 |
			core->arena[(pos + 4) % MEM_SIZE]);
	return (ret);
}
