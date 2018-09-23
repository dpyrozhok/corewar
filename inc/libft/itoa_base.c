/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:45:11 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/05/10 18:45:13 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_base(long long int *i, t_lst *opt, char c)
{
	int		base;

	*i = 0;
	opt->znak = 'n';
	base = (c == 'o') ? 8 : 16;
	base = (c == 'd') ? 10 : base;
	base = (c == 'u') ? 2 : base;
	return (base);
}

char	*ft_i_b_u(char c, unsigned long long int num, t_lst opt, int *n)
{
	long long int		base;
	char				*res;
	long long int		i;

	(c != 'u') ? ft_chang_modif_unsig(&num, opt) : 0;
	res = (char *)(malloc(sizeof(char) * 30));
	base = ft_base(&i, &opt, c);
	(num == 0 && ++i) ? res[0] = '0' : 0;
	while (num > 0)
	{
		if ((c == 'x' || c == 'X') && num % base > 9 && num % base < 17)
			res[i++] = (c == 'x') ? 87 + num % base : 55 + num % base;
		else
			res[i++] = (char)(48 + num % base);
		num = num / base;
	}
	res[i] = '\0';
	res = rev(res);
	if (c == 'u')
		return (res);
	ft_pr_num(res, opt, c, n);
	free(res);
	return (NULL);
}

void	ft_itoa_base(long long int num, t_lst opt, int *n)
{
	char				*res;
	long long int		i;

	i = 0;
	ft_chang_modif(&num, opt);
	if ((res = (char*)(malloc(sizeof(char) * 30))) && num < 0)
	{
		if (num < -9223372036854775807)
		{
			ft_pr_num("-9223372036854775808", opt, '\0', n);
			return ;
		}
		opt.znak = '-';
		num *= -1;
	}
	(num == 0 && ++i) ? res[0] = '0' : 0;
	while (num > 0)
	{
		res[i++] = (char)(48 + num % 10);
		num = num / 10;
	}
	res[i] = '\0';
	res = rev(res);
	ft_pr_num(res, opt, '\0', n);
	free(res);
}
