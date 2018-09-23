/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 17:34:35 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/24 00:50:49 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_check.h"

int			ft_err(int ret, char *str, char *orig)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	if (orig)
	{
		write(2, "\n>>> '", 6);
		write(2, orig, ft_strlen(orig));
		write(2, "'\n", 2);
	}
	else
		write(2, "\n", 1);
	return (ret);
}

int			ft_is_num(char *str)
{
	if (str)
	{
		if (*str == '-' || *str == '+')
			str++;
		if (!*str)
			return (0);
		while (*str)
		{
			if (!ft_isdigit(*str))
				return (0);
			str++;
		}
		return (1);
	}
	return (0);
}

static int	ft_str_include(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*n;

	while (*haystack)
	{
		if (*haystack == *needle)
		{
			h = haystack;
			n = needle;
			while (*h)
			{
				if (*h != *n)
					break ;
				h++;
				n++;
			}
			if (!*n && !*h)
				return (1);
		}
		haystack++;
	}
	return (0);
}

static void	ft_check_filename(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 5)
		exit(ft_err(25, "Invalid file type", str));
	if (!ft_str_include(str, ".cor"))
		exit(ft_err(26, "Invalid file type", str));
}

int			ft_check_dir(char *str)
{
	int		fd;

	fd = open(str, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		exit(ft_err(17, "Argument is not a file", str));
	}
	ft_check_filename(str);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit(ft_err(18, "Unable to open file", str));
	return (fd);
}
