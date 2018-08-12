/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 15:42:49 by amalkevy          #+#    #+#             */
/*   Updated: 2018/01/13 15:50:55 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <fcntl.h>

static t_list				*ft_lst_checkfd(t_list **lst, const int fd)
{
	t_list					*res;

	res = *lst;
	while (res)
	{
		if (res->content_size == (size_t)fd)
			return (res);
		res = res->next;
	}
	res = malloc(sizeof(*res));
	res->content = ft_strdup("\0");
	res->content_size = fd;
	res->next = NULL;
	ft_lstadd(lst, res);
	res = *lst;
	return (res);
}

static int					ft_checkcontent(char **line, char **ostacha)
{
	int						i;
	char					*str;
	int						start;

	i = -1;
	while ((*ostacha)[++i])
		if ((*ostacha)[i] == '\n')
		{
			start = (int)*ostacha;
			start = (int)ft_strchr(*ostacha, '\n') + 1 - start;
			str = (*line);
			*line = ft_strsub(*ostacha, 0, start - 1);
			free(str);
			str = (*ostacha);
			*ostacha = ft_strsub(*ostacha, start
					, (int)ft_strlen(*ostacha) - start);
			free(str);
			return (1);
		}
	str = (*line);
	*line = ft_strjoin(*line, (*ostacha));
	free(str);
	ft_bzero(*ostacha, ft_strlen(*ostacha));
	return (0);
}

int							get_next_line(int fd, char **line)
{
	char					buf[BUFF_SIZE + 1];
	int						ret;
	t_list					*ostacha;
	char					*str;
	static t_list			*lst = NULL;

	ret = 0;
	if (fd < 0 || line == NULL || BUFF_SIZE < 0 || read(fd, buf, 0) < 0)
		return (-1);
	ostacha = ft_lst_checkfd(&lst, fd);
	*line = ft_strdup("\0");
	if (!(ft_strchr(ostacha->content, '\n')))
		while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			str = ostacha->content;
			ostacha->content = ft_strjoin(str, buf);
			str ? free(str) : str;
			if (ft_strchr(ostacha->content, '\n'))
				break ;
		}
	if (ret < BUFF_SIZE && !ft_strlen(ostacha->content))
		return (0);
	ft_checkcontent(line, (char**)(&(ostacha->content)));
	return (1);
}
