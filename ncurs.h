#ifndef NCURS_H
# define NCURS_H
# include <ncurses.h>
# include <pthread.h>
# include "corewar.h"
# include "libft/get_next_line.h"

# include "SDL2-2.0.8/include/SDL.h"
# include "SDL2-2.0.8/include/SDL_audio.h"
# undef main

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

int			ft_print_help(size_t i, size_t j, int fd, char c);
void		ft_draw(t_core *core);
void		ft_init_screen(t_core *core);
void		ft_breakdown(t_core *core);
void		ft_play_sound(char *src);

#endif