/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:51:44 by amalkevy          #+#    #+#             */
/*   Updated: 2018/06/18 12:36:21 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void	ft_obnul(t_my	*inf)
{
    inf->fd = open("test", O_RDONLY);
    inf->t.line = NULL;

}

void    ft_push_back(t_my *lst, t_text *new)
{
    t_text  *p_t;

    p_t = &lst->t;
    while (p_t->next)
    {
        p_t = p_t->next;
    }
    if (p_t->line)
        p_t->next = new;
    else
        lst->t = *new;
}

void    ft_print_txt(t_text t)
{
    t_text      *p_t;

    p_t = &t;
    while (p_t->next)
    {
        ft_printf("%s\t\n", p_t->line);
        p_t = p_t->next;
    }
    if(p_t)
        ft_printf("%s\t\n", p_t->line);
}

int		main()
{
	t_my	inf;
    t_text  *new_t;

	ft_obnul(&inf);
    new_t = malloc(sizeof(new_t));
    new_t->next = NULL;
	while (get_next_line(inf.fd, &(new_t->line)) > 0)
	{

        ft_push_back(&inf, new_t);
        new_t = malloc(sizeof(new_t));
        new_t->next = NULL;
	}
    free(new_t);
    ft_print_txt(inf.t);
	return 0;
}
