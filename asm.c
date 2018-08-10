/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:13:07 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/08/09 13:13:09 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "asm.h"

int		ft_check_format(char *name)
{
    char *format;

    format = ft_strchr(name, '.');
    if (ft_strcmp(format, ".s") == 0)
        return (1);
    else
        return (0);
}

char		*ft_get_name(char *name)
{
	char	*get;
	int		i;

	i = 0;
	while (name[i] != '.')
		i++;
	get = malloc(sizeof(char) * i);
	ft_strncpy(get, name, i);
	return (get);
}

int		main(int ac, char **av)
{
	char *name;

	if (ac < 2 || ac > 3)
		return (ft_printf("Invalid number of arguements")); // inform invalid number of arguement
	// if (ft_strcmp(av[1], "-d")) // decompilyator?
	// {
	// 	if (ac != 3)
	// 		return (0) // nepravilnaya komanda sveti usage(kompil
	// 	// if () nepravilniy format faila
	// 	//return (0);
	// }
	// else
	// {
	// 	// if () nepravilniy format faila
	// 	//return (0);
	// }
	if (!(ft_check_format(av[1])))
		return(ft_printf("Can't read source file\n"));
	else
		name = ft_get_name(av[1]);
	ft_printf("Writing output program to ");
	ft_printf("%s.cor", name);
	free(name);
	return (0);
}