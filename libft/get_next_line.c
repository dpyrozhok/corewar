/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:25:48 by popanase          #+#    #+#             */
/*   Updated: 2018/02/07 18:50:18 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_cut_buff(char *s)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (s[i] != '\n' && s[i])
		i++;
	if (s[i] == '\n')
		i++;
	while (s[i])
	{
		s[j] = s[i];
		i++;
		j++;
	}
	s[j] = '\0';
}

void	ft_cut_str(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	s[i] = '\0';
}

int		get_next_line(const int fd, char **line)
{
	static char	sb[BUFF_SIZE + 1];
	char		*tmp;
	char		b[BUFF_SIZE + 1];
	int			r;

	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 || read(fd, b, 0) == -1)
		return (-1);
	*line = ft_strdup(sb);
	while (!ft_strchr(sb, '\n') && (r = read(fd, b, BUFF_SIZE)))
	{
		b[r] = '\0';
		ft_strcpy(sb, b);
		tmp = ft_strjoin(*line, sb);
		free(*line);
		*line = tmp;
	}
	if (!ft_strlen(sb) && r < BUFF_SIZE)
		return (0);
	ft_cut_buff(sb);
	ft_cut_str(*line);
	return (1);
}
