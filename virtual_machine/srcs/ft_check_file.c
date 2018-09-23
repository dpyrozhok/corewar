/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 17:33:18 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/24 00:50:41 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_check.h"

static void	ft_check_null(t_check *file)
{
	int i;

	if (file->ret != 4)
	{
		ft_err(19, "Bot NULL bytes length mismatch", ft_itoa((int)file->ret));
		exit(19);
	}
	i = 0;
	while (i < 4)
	{
		if (file->buf[i] != '\0')
			exit(ft_err(20, "Invalid NULL bytes", NULL));
		i++;
	}
}

static void	ft_check_size(int fd, t_check **file)
{
	(*file)->size = (unsigned int)((unsigned char)(*file)->buf[0] << 24 \
		| (unsigned char)(*file)->buf[1] << 16 \
		| (unsigned char)(*file)->buf[2] << 8 \
		| (unsigned char)(*file)->buf[3]);
	if ((*file)->size > CHAMP_MAX_SIZE)
		exit(ft_err(21, "Exceeded bot max size", NULL));
	(*file)->ret = read(fd, &(*file)->comment, COMMENT_LENGTH);
	if ((*file)->ret != COMMENT_LENGTH)
	{
		ft_err(22, "Bot comment length mismatch", ft_itoa((int)(*file)->ret));
		exit(22);
	}
	(*file)->ret = read(fd, &(*file)->buf, 4);
	ft_check_null((*file));
	(*file)->code = (unsigned char *)ft_memalloc(sizeof(unsigned char) * \
		(*file)->size);
	(*file)->ret = read(fd, (*file)->code, CHAMP_MAX_SIZE);
	if ((*file)->ret != (*file)->size)
		exit(ft_err(23, "Bot size mismatch", ft_itoa((int)(*file)->ret)));
	ft_strclr((*file)->buf);
	(*file)->ret = read(fd, &(*file)->buf, 1);
	if ((*file)->ret > 0)
		exit(ft_err(24, "Invalid bot size", NULL));
	free((*file)->code);
	free(*file);
}

void		ft_check_file(char *str, int *bots, t_check *file)
{
	int		fd;

	fd = ft_check_dir(str);
	file = (t_check *)ft_memalloc(sizeof(t_check));
	file->ret = read(fd, &file->buf, 4);
	file->size = (unsigned int)((unsigned char)file->buf[0] << 24 \
		| (unsigned char)file->buf[1] << 16 \
		| (unsigned char)file->buf[2] << 8 \
		| (unsigned char)file->buf[3]);
	if (file->ret != 4 || file->size != COREWAR_EXEC_MAGIC)
		exit(ft_err(14, "Invalid magic bytes", NULL));
	file->ret = read(fd, &file->name, PROG_NAME_LENGTH);
	if (file->ret != PROG_NAME_LENGTH)
		exit(ft_err(15, "Bot name length mismatch", ft_itoa((int)file->ret)));
	file->ret = read(fd, &file->buf, 4);
	ft_check_null(file);
	file->ret = read(fd, &file->buf, 4);
	if (file->ret != 4)
	{
		ft_err(16, "Bot max size length mismatch", ft_itoa((int)file->ret));
		exit(16);
	}
	ft_check_size(fd, &file);
	close(fd);
	*bots += 1;
}
