#ifndef NCURS_H
# define NCURS_H
# include <ncurses.h>
# include <pthread.h>
# include "corewar.h"
# include "libft/get_next_line.h"

# include "SDL2/include/SDL.h"
# include "SDL2/include/SDL_audio.h"
# undef main

int			p_help(size_t i, size_t j, int fd, char c);
void		do_win(void);
void		do_ncurs(t_core *core);
void		do_acs(void);
void		init_ncurs(t_core *core);
void		do_last(t_core *core);
void		play(char *src);

#endif