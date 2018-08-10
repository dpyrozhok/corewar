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

//void	ft_obnul(t_my	*inf)
//{
//	inf->fd = open("test", O_RDONLY);
//}


//void    ft_push_back(t_text **lst, t_text *new)
//{
//    t_text  *p_t;
//
//    p_t = *lst;
//    if (!p_t)//->line)
//        p_t = new;
//    else
//    {
//        while (p_t->next)
//        {
//            p_t = p_t->next;
//        }
//        p_t->next = new;
//        p_t = p_t->next;
//        p_t->next = NULL;
//    }
//    p_t->next = NULL;
//}

void    ft_push_back(t_text *lst, t_text *new)
{
    t_text  *p_t;

    p_t = lst;
    while (p_t->next)
    {
        p_t = p_t->next;
    }
    if (p_t->line)
        p_t->next = new;
    else
        lst = new;
}

void    ft_print_txt(t_text *p_t)
{
    while (p_t->next)
    {
        ft_printf("%s\n", p_t->line);
        p_t = p_t->next;
    }
    if(p_t)
        ft_printf("%s\n", p_t->line);
}

int		main()
{
	t_my	inf;
	t_text	*p_t;
    t_text  *new_t;

//	ft_obnul(&inf);
    inf.fd = open("test", O_RDONLY);
	inf.t.line = NULL;
    inf.t.next = NULL;
    p_t = &inf.t;
    new_t = malloc(sizeof(new_t));
	while (get_next_line(inf.fd, &(new_t->line)) > 0)
	{
        new_t->next = NULL;
        ft_push_back(&inf.t, new_t);
        new_t = malloc(sizeof(new_t));
	}
    free(new_t);
    p_t = &inf.t;
    ft_print_txt(p_t);
	return 0;
}
