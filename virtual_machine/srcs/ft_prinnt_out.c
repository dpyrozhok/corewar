/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prinnt_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 11:40:45 by popanase          #+#    #+#             */
/*   Updated: 2018/09/24 00:48:18 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_introduce(t_core *core)
{
	t_champ	*tmp;

	ft_printf("Introducing contestants...");
	tmp = core->champs;
	while (tmp)
	{
		ft_printf("\n* Player %i, weighing %i bytes, \"%s\" (\"%s\") !", \
		tmp->id, tmp->size, tmp->name, tmp->comment);
		tmp = tmp->next;
	}
}

void	ft_dump(t_core *core)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
		{
			ft_printf("\n%#06x : ", i);
		}
		ft_printf("%02x ", core->arena[i]);
		i++;
	}
	ft_printf("\n");
}

void	ft_winner_is(t_core *core)
{
	t_champ	*champ;

	champ = core->champs;
	while (champ)
	{
		if (champ->id == core->winner_id)
			ft_printf("\nPlayer %i (%s) won\n", \
				champ->id, champ->name);
		champ = champ->next;
	}
}
