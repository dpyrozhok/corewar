/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:44:45 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/05/10 18:44:47 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		n_bits(unsigned int num, t_lst opt, int *n)
{
	int		num_bits;
	char	*p;

	p = ft_i_b_u('u', num, opt, n);
	num_bits = ft_strlen(p);
	free(p);
	num_bits /= 2;
	if (num_bits < 4)
		num_bits = 1;
	else if (num_bits >= 4 && num_bits <= 5)
		num_bits = 2;
	else if (num_bits >= 6 && num_bits <= 8)
		num_bits = 3;
	else
		num_bits = 4;
	return (num_bits);
}

int		ft_count_pr_b(wchar_t *str, t_lst opt, int *n)
{
	int		i;
	int		pr_b;

	i = 0;
	pr_b = 0;
	if (opt.precis == -1)
		while (str && str[i])
			pr_b += n_bits(str[i++], opt, n);
	while (opt.precis > 0 && str[i])
	{
		opt.precis -= n_bits(str[i], opt, n);
		if (opt.precis >= 0)
			pr_b += n_bits(str[i++], opt, n);
	}
	return (pr_b);
}

void	ft_unicode_s(va_list args, t_lst opt, int *n)
{
	wchar_t			*str;
	unsigned int	c;
	int				anum_bits;
	int				num_bits;
	int				i;

	i = 0;
	str = va_arg(args, wchar_t*);
	if (!str)
		ft_pstr(NULL, opt, n, 's');
	anum_bits = ft_count_pr_b(str, opt, n);
	num_bits = anum_bits;
	while (opt.vyravn != 'l' && opt.width-- > anum_bits && ++(*n))
		(opt.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
	while (anum_bits > 0)
	{
		c = (unsigned int)n_bits(str[i], opt, n);
		ft_pr_unic_char(str[i++], n, c);
		anum_bits -= c;
	}
	while (opt.vyravn == 'l' && opt.width-- > num_bits && ++(*n))
		(opt.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
}

void	ft_unicode_c(va_list args, t_lst opt, int *n)
{
	unsigned int	c;
	int				num_bits;

	c = (unsigned int)va_arg(args, wint_t);
	num_bits = n_bits(c, opt, n);
	while (opt.vyravn != 'l' && opt.width-- > num_bits && ++(*n))
		(opt.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
	ft_pr_unic_char(c, n, num_bits);
	while (opt.vyravn == 'l' && opt.width-- > num_bits && ++(*n))
		(opt.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
}
