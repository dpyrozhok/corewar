/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 18:05:18 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/24 00:53:34 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_visual.h"

static void	*ft_resize_help(void *ptr)
{
	if (!ptr)
		while (true)
		{
			if (LINES < 24 || COLS < 80)
			{
				clear();
				refresh();
				endwin();
				system("reset");
				ft_play_sound("virtual_machine/sounds/Track0.wav");
				printf("'corewar' shut down. Resize window to min "
					"80 cols and 24 rows. Currently %d cols and %d rows.\n", \
					COLS, LINES);
				exit(31);
			}
		}
	return (NULL);
}

static int	ft_init_help(void)
{
	pthread_t	thread_resize_help;

	initscr();
	if (LINES < 24 || COLS < 80)
	{
		endwin();
		ft_play_sound("virtual_machine/sounds/Track0.wav");
		printf("Resize window to min 80 cols and 24 rows. Currently %d cols"
			" and %d rows.\n", COLS, LINES);
		exit(30);
	}
	pthread_create(&thread_resize_help, NULL, ft_resize_help, NULL);
	pthread_detach(thread_resize_help);
	raw();
	keypad(stdscr, TRUE);
	noecho();
	if (has_colors() == FALSE)
	{
		endwin();
		ft_printf("Your terminal does not support color\n");
		return (1);
	}
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	return (0);
}

static int	ft_get_response(void)
{
	char	c;

	attron(COLOR_PAIR(1));
	printw("Press 'c' to continue or 'q' to quit");
	refresh();
	attroff(COLOR_PAIR(1));
	while (1)
	{
		read(0, &c, 1);
		if (c == '\121' || c == '\161')
		{
			endwin();
			return (1);
		}
		if (c == '\103' || c == '\143')
			break ;
	}
	clear();
	move(0, 0);
	return (0);
}

static void	ft_print_man(size_t *i, size_t j, char c, char *str)
{
	char	p;

	p = str[*i];
	*i += 1;
	if (*i < j)
	{
		c = str[*i];
		if (p == '/' && c == '*')
			attron(A_BOLD);
		else if (p == '*' && c == '/')
			attroff(A_BOLD);
		else if (p == '/' && c == '^')
			attron(COLOR_PAIR(1));
		else if (p == '^' && c == '/')
			attroff(COLOR_PAIR(1));
		else
		{
			printw("%c", p);
			return ;
		}
	}
	else
		printw("%c", p);
	*i += 1;
	refresh();
}

int			ft_print_help(size_t i, size_t j, int fd, char c)
{
	int		row_col[2];
	int		y_x[2];
	char	*str;

	if (ft_init_help())
		return (2);
	while (get_next_line(fd, &str) > 0)
	{
		getmaxyx(stdscr, row_col[0], row_col[1]);
		getyx(stdscr, y_x[0], y_x[1]);
		if (y_x[0] == (row_col[0] - 1))
		{
			if (ft_get_response())
				return (0);
		}
		i = 0;
		j = ft_strlen(str);
		while (i < j)
			ft_print_man(&i, j, '\0', str);
		printw("\n");
	}
	read(0, &c, 1);
	endwin();
	return (0);
}
