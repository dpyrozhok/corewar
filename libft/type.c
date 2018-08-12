/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:45:24 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/05/10 18:45:25 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_chang_modif(long long int *num, t_lst opt)
{
	if (opt.modif == '0')
		*num = (int)(*num);
	if (opt.modif == '1')
		*num = (signed char)(*num);
	if (opt.modif == '2')
		*num = (short)(*num);
	if (opt.modif == '3')
		*num = (long)(*num);
	if (opt.modif == '5')
		*num = (intmax_t)(*num);
	if (opt.modif == '6')
		*num = (size_t)(*num);
}

void	ft_chang_modif_unsig(unsigned long long int *num, t_lst opt)
{
	if (opt.modif == '0')
		*num = (unsigned int)(*num);
	if (opt.modif == '1')
		*num = (unsigned char)(*num);
	if (opt.modif == '2')
		*num = (unsigned short int)(*num);
	if (opt.modif == '3')
		*num = (unsigned long int)(*num);
	if (opt.modif == '5')
		*num = (uintmax_t)(*num);
	if (opt.modif == '6')
		*num = (size_t)(*num);
}

void	ft_pointer(va_list args, t_lst opt, int *n)
{
	unsigned long int	p;
	char				*s;

	if (opt.type == 'p')
	{
		p = (unsigned long)va_arg(args, void*);
		opt.h = 'y';
		opt.modif = '4';
		ft_i_b_u('x', p, opt, n);
	}
	else
	{
		s = malloc(sizeof(char) * 2);
		s[0] = va_arg(args, int);
		s[1] = '\0';
		ft_pstr(s, opt, n, 'c');
		free(s);
	}
}

void	ft_type(char c, t_lst *opt, va_list args, int *n)
{
	long long int		i;

	opt->type = c;
	if (c == 's' && opt->modif != '3')
		ft_pstr(va_arg(args, char *), *opt, n, 's');
	else if (c == 'S' || (c == 's' && opt->modif == '3'))
		ft_unicode_s(args, *opt, n);
	else if (c == 'c' && opt->modif != '3')
		ft_pointer(args, *opt, n);
	else if (c == 'C' || (c == 'c' && opt->modif == '3'))
		ft_unicode_c(args, *opt, n);
	else if (c == 'p')
		ft_pointer(args, *opt, n);
	else
	{
		(opt->tochn_bool == 'y') ? opt->nul = 'n' : 0;
		(c == 'D' || c == 'U' || c == 'O') ? ft_modific("l", opt) : 0;
		i = va_arg(args, long long int);
		(c == 'i' || c == 'd' || c == 'D') ? ft_itoa_base(i, *opt, n) : 0;
		if (c == 'x' || c == 'X')
			(c == 'x') ? ft_i_b_u('x', i, *opt, n) : ft_i_b_u('X', i, *opt, n);
		else if (c == 'o' || c == 'O' || c == 'u' || c == 'U')
			(c == 'o' || c == 'O') ? ft_i_b_u('o', i, *opt, n) :
		ft_i_b_u('d', i, *opt, n);
	}
}
