/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:08:53 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/03 15:50:53 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>
# include <limits.h>
# include <fcntl.h>
// # include <types.h>
// # include <stat.h
# define BUFF_SIZE 1

void				*ft_memset(void *dest, int c, size_t n);
void				ft_bzero(void *dest, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
	size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_countw(char **s);
char				**ft_strsort(char **s);
char				*ft_strrev(char *s);
int					*ft_intsort(int *a, size_t n, char order);
int					*ft_intrev(int *s, size_t n);

t_list				*ft_check_fd(t_list *ostatok, int fd, char **line);
void				ft_del_lst(t_list **start, t_list *goal);
int					check_newline_inlst(t_list **ost, char **line, t_list *tmp);
int					check_n_inbuf(char *buf, t_list **lst, char **line, int fd);
int					get_next_line(const int fd, char **line);

typedef struct		s_lst
{
	char			znak;
	int				width;
	int				precis;
	char			modif;
	char			vyravn;
	char			tochn_bool;
	char			nul;
	char			h;
	char			type;
}					t_lst;

void				ft_chang_modif(long long int *num, t_lst opt);
void				ft_chang_modif_unsig(unsigned long long int *n, t_lst o);
void				ft_pointer(va_list args, t_lst opt, int *n);
void				ft_type(char c, t_lst *opt, va_list args, int *n);
int					ft_base(long long int *i, t_lst *opt, char c);
char				*ft_i_b_u(char c, unsigned long long int z, t_lst o,
	int *n);
void				ft_itoa_base(long long int num, t_lst opt, int *n);
char				*rev(char *start);
void				ft_pr_num2(t_lst opt, int *spaces, int *n, int *l);
int					ft_spaces(t_lst o, char *s, int l, char c);
void				ft_pr_num(char *s, t_lst o, char c, int *n);
void				ft_pstr(char *s, t_lst opt, int *n, char c);
int					n_bits(unsigned int num, t_lst opt, int *n);
int					ft_count_pr_b(wchar_t *str, t_lst opt, int *n);
void				ft_unicode_s(va_list args, t_lst opt, int *n);
void				ft_unicode_c(va_list args, t_lst opt, int *n);
void				ft_one_bit(unsigned int num);
void				ft_two_bit(unsigned int num);
void				ft_three_bit(unsigned int num);
void				ft_four_bit(int *n, unsigned int num);
void				ft_pr_unic_char(unsigned int num, int *n, int size);
void				ft_flag(char c, t_lst *option);
char				*ft_precision(char *str, t_lst *option);
char				*ft_width(char *str, t_lst *option);
char				*ft_modific_2(char *str, t_lst *option);
char				*ft_modific(char *str, t_lst *option);
void				creat_lst(t_lst *opt);
char				is_param(char *c);
int					ft_som_els(char **str, t_lst *option, int *n);
char				*ft_check(char *str, t_lst *option, va_list args, int *n);
int					ft_printf(char *str, ...);

#endif
