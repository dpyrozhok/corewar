/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:32:13 by popanase          #+#    #+#             */
/*   Updated: 2018/09/24 01:16:39 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include "libft.h"

int				ft_printf(const char *fmt, ...);

typedef struct	s_fmt
{
	int		shrp;
	int		spc;
	int		zrs;
	int		mns;
	int		pls;
	size_t	fwdth;
	int		prcs;
	size_t	prcs_v;
	int		md;
	char	cnv;
	char	*s;
	int		ret;
}				t_fmt;

void			ft_strexp_b(t_fmt *f, char c, size_t n);
void			ft_strexp_e(t_fmt *f, char c, size_t n);
void			ft_conver_x(va_list ap, t_fmt *format);
void			ft_conver_o(va_list ap, t_fmt *format);
void			ft_conver_s(va_list ap, t_fmt *format);
void			ft_conver_c(va_list ap, t_fmt *format);
void			ft_conver_id(va_list ap, t_fmt *format);
void			ft_conver_u(va_list ap, t_fmt *format);
void			ft_conver_per(t_fmt *format);
void			ft_conver_p(va_list ap, t_fmt *format);
void			ft_conver_lc(va_list ap, t_fmt *format);
void			ft_conver_ls(va_list ap, t_fmt *format);
void			ft_conver_inv(t_fmt *format);
int				ft_iscnv(char c);
int				ft_skip(char c);
void			ft_read_md(const char *f, t_fmt *format);
void			ft_read_format(const char *f, t_fmt *format);
int				ft_count_bits(wchar_t lc);
size_t			ft_wclen(wchar_t lc);
size_t			ft_wstrlen(wchar_t *ls);
size_t			ft_getwdth(wchar_t *ls, t_fmt *f);
int				ft_check_type(wchar_t *ls);
size_t			ft_putwchar(wchar_t lc);
int				ft_free_format(t_fmt *format);
void			ft_handle_flags_c(char c, t_fmt *f);
void			ft_handle_flags_s(t_fmt *f);

#endif
