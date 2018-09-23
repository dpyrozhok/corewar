/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visual.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 17:44:04 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/24 01:28:27 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISUAL_H
# define FT_VISUAL_H
# include <ncurses.h>
# include <pthread.h>
# include "corewar.h"
# include "../../libft/includes/libft.h"
# include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
# include "/Library/Frameworks/SDL2.framework/Headers/SDL_audio.h"

# define BORDER_LS ACS_VLINE
# define BORDER_RS ACS_VLINE
# define BORDER_TS ACS_HLINE
# define BORDER_BS ACS_HLINE
# define BORDER_TL ACS_ULCORNER
# define BORDER_TR ACS_URCORNER
# define BORDER_BL ACS_LLCORNER
# define BORDER_BR ACS_LRCORNER

# define TITLE_FG COLOR_CYAN
# define TITLE_BG COLOR_BLACK

# define BORDER_L_FG COLOR_RED
# define BORDER_L_BG COLOR_WHITE

# define BORDER_R_FG COLOR_BLUE
# define BORDER_R_BG COLOR_WHITE

# define DEFAULT_FG COLOR_WHITE
# define DEFAULT_BG COLOR_BLACK

# define BOT_BG COLOR_BLACK
# define BOT_A_FG COLOR_GREEN
# define BOT_B_FG COLOR_MAGENTA
# define BOT_C_FG COLOR_BLUE
# define BOT_D_FG COLOR_RED

# define CAR_FG COLOR_WHITE

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
void			ft_init_win(t_core *core);
void			ft_fill_screen(t_core *core);
void			ft_breakdown(t_core *core);
void			ft_play_sound(char *src);
void			ft_vcars_on(t_core *core, t_car *car, int ag, int pos);
void			ft_vcars_check(t_core *core, t_car *tmp);
void			ft_vcars_off(t_core *core, t_car *tmp);
void			ft_vcars_norev(t_core *core, t_car *car);
void			ft_vcars_rev(t_core *core, t_car *car);
void			ft_champ_visual(t_core *core, t_champ *tmp, int shift);
void			ft_vcars_fork(t_core *core, t_car *car, int pos);
void			*ft_resize(void *ptr);
void			ft_vcars_opcode(t_core *core, t_car *car);

#endif
