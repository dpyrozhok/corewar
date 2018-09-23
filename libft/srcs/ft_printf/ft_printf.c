/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:44:18 by popanase          #+#    #+#             */
/*   Updated: 2018/03/19 17:58:28 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

void		ft_strexp_b(t_fmt *f, char c, size_t n)
{
	char	*new;
	size_t	i;

	new = ft_strnew(ft_strlen(f->s) + n);
	i = 0;
	while (i < n)
		new[i++] = c;
	ft_strcpy(new + n, f->s);
	free(f->s);
	f->s = new;
}

void		ft_strexp_e(t_fmt *f, char c, size_t n)
{
	char	*new;
	size_t	i;
	size_t	len;

	len = ft_strlen(f->s) + n;
	new = ft_strnew(len);
	ft_strcpy(new, f->s);
	i = ft_strlen(f->s);
	while (i < len)
		new[i++] = c;
	free(f->s);
	f->s = new;
}

void		ft_make_cnv(va_list ap, t_fmt *format)
{
	if (format->cnv == 'S' || (format->cnv == 's' && format->md == 3))
		ft_conver_ls(ap, format);
	else if (format->cnv == 's')
		ft_conver_s(ap, format);
	else if (format->cnv == 'C' || (format->cnv == 'c' && format->md == 3))
		ft_conver_lc(ap, format);
	else if (format->cnv == 'c')
		ft_conver_c(ap, format);
	else if (format->cnv == '%')
		ft_conver_per(format);
	else if (format->cnv == 'p')
		ft_conver_p(ap, format);
	else if (format->cnv == 'i' || format->cnv == 'd' || format->cnv == 'D')
		ft_conver_id(ap, format);
	else if (format->cnv == 'u' || format->cnv == 'U')
		ft_conver_u(ap, format);
	else if (format->cnv == 'o' || format->cnv == 'O')
		ft_conver_o(ap, format);
	else if (format->cnv == 'x' || format->cnv == 'X')
		ft_conver_x(ap, format);
	else
		ft_conver_inv(format);
}

void		ft_do_printf(const char *f, va_list ap, int *r)
{
	t_fmt	*format;

	while (*f)
	{
		if (*f == '%')
		{
			f++;
			format = (t_fmt *)ft_memalloc(sizeof(t_fmt));
			ft_read_format(f, format);
			ft_make_cnv(ap, format);
			if (format->ret == -1 && (*r = -1) && ft_free_format(format))
				break ;
			*r += format->ret;
			ft_free_format(format);
			while (ft_skip(*f))
				f++;
		}
		else
		{
			ft_putchar(*f);
			(*r)++;
		}
		if (*f)
			f++;
	}
}

int			ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		r;

	r = 0;
	va_start(ap, fmt);
	ft_do_printf(fmt, ap, &r);
	va_end(ap);
	return (r);
}
