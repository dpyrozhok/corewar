/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 17:44:04 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/18 20:54:33 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURS_H
# define NCURS_H
# include <ncurses.h>
# include <pthread.h>
# include "corewar.h"
# include "libft/get_next_line.h"

# include "SDL2-2.0.8/include/SDL.h"
# include "SDL2-2.0.8/include/SDL_audio.h"
# undef main

# define WIN_ROWS 69
# define WIN_COLS 254

# define BORDER_L_HEIGHT 67
# define BORDER_L_WIDTH 196
# define BORDER_L_START_Y 1
# define BORDER_L_START_X 0

# define BORDER_R_HEIGHT 67
# define BORDER_R_WIDTH 56
# define BORDER_R_START_Y 1
# define BORDER_R_START_X 197

# define BORDER_LS ACS_VLINE
# define BORDER_RS ACS_VLINE
# define BORDER_TS ACS_HLINE
# define BORDER_BS ACS_HLINE
# define BORDER_TL ACS_ULCORNER
# define BORDER_TR ACS_URCORNER
# define BORDER_BL ACS_LLCORNER
# define BORDER_BR ACS_LRCORNER

# define TITLE_COLOR 1
# define TITLE_FG COLOR_CYAN
# define TITLE_BG COLOR_BLACK

# define BORDER_L_COLOR 2
# define BORDER_L_FG COLOR_RED
# define BORDER_L_BG COLOR_WHITE

# define BORDER_R_COLOR 3
# define BORDER_R_FG COLOR_BLUE
# define BORDER_R_BG COLOR_WHITE

# define DEFAULT_COLOR 4
# define DEFAULT_FG COLOR_WHITE
# define DEFAULT_BG COLOR_BLACK

# define BOT_BG COLOR_BLACK
# define BOT_A_FG COLOR_GREEN
# define BOT_B_FG COLOR_MAGENTA
# define BOT_C_FG COLOR_BLUE
# define BOT_D_FG COLOR_RED
# define BOT_A_COLOR 20
# define BOT_B_COLOR 21
# define BOT_C_COLOR 22
# define BOT_D_COLOR 23

# define CAR_FG COLOR_WHITE
# define CAR_A_COLOR 30
# define CAR_B_COLOR 31
# define CAR_C_COLOR 32
# define CAR_D_COLOR 33

typedef struct	s_border
{
	int	startx;
	int	starty;
	int	height;
	int	width;
}				t_border;

int				ft_print_help(size_t i, size_t j, int fd, char c);
void			ft_draw(t_core *core);
void			ft_init_screen(t_core *core, int i, int r, int c);
void			ft_breakdown(t_core *core);
void			ft_play_sound(char *src);

#endif
