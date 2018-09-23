/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_num_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:44:23 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/05/10 18:44:27 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*rev(char *start)
{
	char				*new;
	char				*end;
	char				*new_start;

	if (*start == '\0')
		return (NULL);
	end = start;
	new = ft_strnew(ft_strlen(start));
	new_start = new;
	while (*end)
		end++;
	end--;
	*new++ = *end;
	while (end - start != 0)
		*new++ = *(--end);
	free(start);
	return (new_start);
}

void	ft_pr_num2(t_lst opt, int *spaces, int *n, int *l)
{
	(*l) = (opt.precis > (*l)) ? opt.precis - (*l) : 0;
	if (opt.h == 'y' && (opt.type == 'o' || opt.type ==
		'x' || opt.type == 'X' || opt.type == 'p') && opt.nul != 'n' && ++(*n))
	{
		write(1, "0", 1);
		(*spaces)--;
		if (opt.type != 'o' && ++(*n))
			(opt.type == 'X') ? write(1, "X", 1) : write(1, "x", 1);
		(*spaces)--;
	}
	if (opt.znak != 'n' && opt.nul != 'n' && ++(*n))
		write(1, &opt.znak, 1);
	while ((*spaces) > 0 && opt.vyravn == 'n' && ++(*n))
	{
		(opt.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
		(*spaces)--;
	}
}

int		ft_spaces(t_lst o, char *s, int l, char c)
{
	int spaces;

	spaces = (o.precis > l) ? o.precis : l;
	spaces = (o.znak != 'n') ? spaces + 1 : spaces;
	spaces = (*s == '0' && o.precis == 0) ? 0 : spaces;
	spaces = (o.width > spaces) ? o.width - spaces : 0;
	spaces = (c == 'x' && o.h == 'y' && o.nul == 'n' && (*s != '0'
		|| o.type == 'p')) ? spaces - 2 : spaces;
	spaces = (c == 'o' && o.h == 'y') ? spaces - 1 : spaces;
	return (spaces);
}

void	ft_pr_num(char *s, t_lst o, char c, int *n)
{
	int					spaces;
	int					l;

	l = (s != NULL) ? ft_strlen(s) : 0;
	spaces = (ft_spaces(o, s, l, c) > 0) ? ft_spaces(o, s, l, c) : 0;
	ft_pr_num2(o, &spaces, n, &l);
	(c == 'x' && o.h == 'y' && o.nul == 'n' && (*s != '0' ||
		o.type == 'p') && (*n += 2)) ? write(1, "0x", 2) : 0;
	(c == 'X' && o.h == 'y' && o.nul == 'n' && *s != '0' &&
	(*n += 2)) ? write(1, "0X", 2) : 0;
	if (c == 'o' && o.h == 'y' && o.nul == 'n' && ++(*n))
	{
		write(1, "0", 1);
		l--;
	}
	if (o.znak != 'n' && o.nul == 'n' && ++(*n))
		write(1, &o.znak, 1);
	while (l-- > 0 && ++(*n))
		write(1, "0", 1);
	if (s != NULL && !(*s == '0' && o.precis == 0) && !(*s == '0'
		&& o.type == 'o' && o.h == 'y') && ((*n) += ft_strlen(s)))
		ft_putstr(s);
	while (spaces-- && o.vyravn == 'l' && ++(*n))
		(o.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
}

void	ft_pstr(char *s, t_lst opt, int *n, char c)
{
	int					l;
	int					i;
	int					m;

	m = 0;
	if (!s)
	{
		m = 1;
		s = malloc(sizeof(char) * 7);
		s = ft_strcpy(s, "(null)");
	}
	l = (*s == '\0' && c == 'c') ? 1 : ft_strlen(s);
	l = (l > opt.precis && (opt.precis != -1 && !(*s == '\0' && c == 'c')))
		? opt.precis : l;
	i = (opt.width > l && opt.vyravn != 'l') ? (opt.width - l) : 0;
	while (opt.vyravn != 'l' && i > 0 && i > 0 && i-- && ++(*n))
		(opt.nul == 'n') ? write(1, " ", 1) : write(1, "0", 1);
	(*s == '\0' && c == 'c' && ++(*n)) ? write(1, "\0", 1) : 0;
	if (*s)
		while (i < l && ++(*n))
			write(1, &s[i++], 1);
	i = (opt.width > l && opt.vyravn == 'l') ? (opt.width - l) : 0;
	while (i-- && opt.vyravn == 'l')
		(opt.nul == 'n' && ++(*n)) ? write(1, " ", 1) : 0;
	(m == 1) ? free(s) : 0;
}
