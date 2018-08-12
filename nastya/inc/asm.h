/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 12:24:52 by amalkevy          #+#    #+#             */
/*   Updated: 2018/06/19 12:33:08 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"

typedef struct		s_text
{
	char		*line;
	struct s_text	*next;
}                   t_text;

typedef struct s_my
{
	t_text t;
	int fd;
}               t_my;

#endif
