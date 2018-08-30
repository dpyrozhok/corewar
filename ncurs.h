#ifndef NCURS_H
# define NCURS_H
# include <ncurses.h>
# include <pthread.h>
//# include "SDL2-2.0.8/include/SDL.h"
//# include "SDL2-2.0.8/include/SDL_audio.h"
# include "corewar.h"
# include "libft/get_next_line.h"
// # include "SDL2-2.0.8/x86_64-w64-mingw32/include/SDL2/SDL.h"
// #undef main

int			p_help(size_t i, size_t j, int fd, char c);
void		do_win(void);
void		do_ncurs(t_core *core);
void		do_acs(void);
void		init_ncurs(void);
void		do_last(t_core *core);
void		play(char *src);

#endif