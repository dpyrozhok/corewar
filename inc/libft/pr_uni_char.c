/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_uni_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:46:06 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/05/10 18:46:08 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_one_bit(unsigned int num)
{
	unsigned char	octet;

	octet = (unsigned char)num;
	write(1, &octet, 1);
}

void	ft_two_bit(unsigned int num)
{
	unsigned int	mask1;
	unsigned char	o2;
	unsigned char	o1;
	unsigned char	octet;

	mask1 = 49280;
	o2 = (num << 26) >> 26;
	o1 = ((num >> 6) << 27) >> 27;
	octet = (mask1 >> 8) | o1;
	write(1, &octet, 1);
	octet = ((mask1 << 24) >> 24) | o2;
	write(1, &octet, 1);
}

void	ft_three_bit(unsigned int num)
{
	unsigned int	mask2;
	unsigned char	o3;
	unsigned char	o2;
	unsigned char	o1;
	unsigned char	octet;

	mask2 = 14712960;
	o3 = (num << 26) >> 26;
	o2 = ((num >> 6) << 26) >> 26;
	o1 = ((num >> 12) << 28) >> 28;
	octet = (mask2 >> 16) | o1;
	write(1, &octet, 1);
	octet = ((mask2 << 16) >> 24) | o2;
	write(1, &octet, 1);
	octet = ((mask2 << 24) >> 24) | o3;
	write(1, &octet, 1);
}

void	ft_four_bit(int *n, unsigned int num)
{
	unsigned char	o4;
	unsigned char	o3;
	unsigned char	o2;
	unsigned char	o1;
	unsigned char	octet;

	(*n) += 4;
	o4 = (num << 26) >> 26;
	o3 = ((num >> 6) << 26) >> 26;
	o2 = ((num >> 12) << 26) >> 26;
	o1 = ((num >> 18) << 29) >> 29;
	octet = (4034953344 >> 24) | o1;
	write(1, &octet, 1);
	octet = ((4034953344 << 8) >> 24) | o2;
	write(1, &octet, 1);
	octet = ((4034953344 << 16) >> 24) | o3;
	write(1, &octet, 1);
	octet = ((4034953344 << 24) >> 24) | o4;
	write(1, &octet, 1);
}

void	ft_pr_unic_char(unsigned int num, int *n, int size)
{
	if (size == 1 && ((*n) += 1))
		ft_one_bit(num);
	else if (size == 2 && ((*n) += 2))
		ft_two_bit(num);
	else if (size == 3 && ((*n) += 3))
		ft_three_bit(num);
	else
		ft_four_bit(n, num);
	return ;
}
