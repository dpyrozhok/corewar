/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 17:44:04 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/20 15:16:09 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurs.h"

Uint32		g_len;
Uint8		*g_buf;

int		ft_init_help(void)
{
	initscr();
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

int		ft_get_response(void)
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

void	ft_print_man(size_t *i, size_t j, char c, char *str)
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

int		ft_print_help(size_t i, size_t j, int fd, char c)
{
	int		row_col[2];
	int		y_x[2];
	char	*str;

	if (ft_init_help())
		return (6);
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

void	*ft_resize_win(void *ptr)
{
	t_core	*p;

	p = (t_core *)ptr;
	while (true)
	{
		if (LINES < 69 || COLS < 254)
		{
			pthread_mutex_lock(&(p)->m);
			clear();
			refresh();
			endwin();
			system("reset");
			SDL_Quit();
			ft_play_sound("Track0.wav");
			ft_printf("'corewar' shut down unexpectedly. Resize window to min "
				"254 cols and 69 rows. Currently %d cols and %d rows.\n", \
				COLS, LINES);
			exit(122);
			pthread_mutex_unlock(&(p)->m);
		}
	}
	return (NULL);
}

int		ft_count_dig(int nbr)
{
	int		cnt;

	if (nbr == INT_MIN)
		return (11);
	cnt = 0;
	if (nbr < 0)
	{
		cnt++;
		nbr = -nbr;
	}
	cnt++;
	while (nbr %= 10 > 0)
		cnt++;
	return (cnt);
}

void	ft_fill_score(t_core *core, t_champ *cur, double stp, int remain)
{
	int		i;
	int		j;
	int		col;
	int		ttl;

	i = 0;
	col = 0;
	ttl = 0;
	while (i++ < core->qt_champ)
	{
		ttl = (cur->s_live && (stp * cur->s_live < 1)) ? 1 : stp * cur->s_live;
		if (ttl && remain-- > 0)
			ttl++;
		j = 0;
		attron(A_BOLD | COLOR_PAIR(cur->c));
		while (j++ < ttl)
		{
			mvprintw(core->l, 201 + col, "-");
			col = (col < 50) ? col + 1 : 50;
		}
		attroff(A_BOLD | COLOR_PAIR(cur->c));
		cur = cur->next;
	}
}

void	ft_break_score(t_core *core, t_champ *curr, double step)
{
	int		i;
	int		total;

	i = 0;
	total = 0;
	while (i++ < core->qt_champ)
	{
		if (curr->s_live && (step * curr->s_live < 1))
			total++;
		else
			total += (step * curr->s_live);
		curr = curr->next;
	}
	ft_fill_score(core, core->champs, step, 50 - total);
	attron(COLOR_PAIR(4));
	mvprintw(core->l, 251, "]");
	attroff(COLOR_PAIR(4));
}

void	ft_break_last(t_core *core)
{
	attron(COLOR_PAIR(4));
	mvprintw(core->l, 201, \
		"--------------------------------------------------]");
	attroff(COLOR_PAIR(4));
	if (core->l)
	{
		attron(COLOR_PAIR(4));
		mvprintw(core->l - 3, 201, \
			"--------------------------------------------------]");
		attroff(COLOR_PAIR(4));
	}
}

void	ft_breakdown(t_core *core)
{
	int		i;
	double	sum;
	t_champ	*curr;

	pthread_mutex_lock(&core->m);
	i = 0;
	sum = 0.0;
	curr = core->champs;
	while (i++ < core->qt_champ)
	{
		sum += (double)curr->s_live;
		curr = curr->next;
	}
	if (sum)
		ft_break_score(core, core->champs, 50.0 / sum);
	else
		ft_break_last(core);
	pthread_mutex_unlock(&core->m);
}

void	ft_fill_new(t_core *core, double stp, int remain, int r)
{
	int		i;
	int		j;
	int		col;
	int		ttl;
	t_champ	*cur;

	i = 0;
	col = 0;
	ttl = 0;
	cur = core->champs;
	while (i++ < core->qt_champ)
	{
		ttl = (cur->s_live && (stp * cur->s_live < 1)) ? 1 : stp * cur->s_live;
		if (ttl && remain-- > 0)
			ttl++;
		j = 0;
		attron(A_BOLD | COLOR_PAIR(cur->c));
		while (j++ < ttl)
		{
			mvprintw(r, 201 + col, "-");
			col = (col < 50) ? col + 1 : 50;
		}
		attroff(A_BOLD | COLOR_PAIR(cur->c));
		cur = cur->next;
	}
}

void	ft_new_score(t_core *core, t_champ *curr, double step, int r)
{
	int		i;
	int		total;

	i = 0;
	total = 0;
	while (i++ < core->qt_champ)
	{
		if (curr->s_live && (step * curr->s_live < 1))
			total++;
		else
			total += (step * curr->s_live);
		curr = curr->next;
	}
	ft_fill_new(core, step, 50 - total, r);
	attron(COLOR_PAIR(4));
	mvprintw(core->l, 251, "]");
	attroff(COLOR_PAIR(4));
}

void	ft_scoring(t_core *core, int r)
{
	int		i;
	double	sum;
	t_champ	*curr;

	i = 0;
	sum = 0.0;
	curr = core->champs;
	while (i++ < core->qt_champ)
	{
		sum += (double)curr->s_live;
		curr = curr->next;
	}
	if (sum)
		ft_new_score(core, core->champs, 50.0 / sum, r);
}

void	ft_breaking(t_core *core)
{
	attron(COLOR_PAIR(4) | A_BOLD);
	mvprintw(3, 200, "%s", (core->f) ? "** FINISH ** " : "** RUNNING **");
	if (core->t)
		mvprintw(5, 222, "%-10d", 1000000 / core->t);
	else
		mvprintw(5, 222, "Stealth");
	mvprintw(8, 200, "Cycle : %d", core->cycle);
	mvprintw(10, 200, "Processes : %-10d", core->qt_car);
	if (core->t != 1000000 && core->t)
		mvprintw(12, 200, "Speed: %dx     ", 100000 / core->t);
	else if (core->t)
		mvprintw(12, 200, "Speed: 0.1x        ");
	else
		mvprintw(12, 200, "Speed: Stealth     ");
	attroff(COLOR_PAIR(4) | A_BOLD);
}

void	ft_champing(t_core *core, int *r)
{
	int		i;
	t_champ	*curr;

	attron(COLOR_PAIR(4) | A_BOLD);
	i = 0;
	curr = core->champs;
	while (i++ < core->qt_champ)
	{
		(*r)++;
		mvprintw((*r)++, 214, "%21d", curr->last_live);
		mvprintw(*r, 228, "%7d", curr->s_live);
		*r += 2;
		curr = curr->next;
	}
	(*r)++;
	attroff(COLOR_PAIR(4) | A_BOLD);
}

void	ft_draw(t_core *core)
{
	int		r;
	t_champ	*curr;

	pthread_mutex_lock(&core->m);
	r = 14;
	ft_breaking(core);
	ft_champing(core, &r);
	ft_scoring(core, r);
	r += 4;
	attron(COLOR_PAIR(4) | A_BOLD);
	mvprintw(++r, 215, "%-10d", core->c_to_die);
	if (core->f)
	{
		curr = ft_get_champ(core, core->winner_id);
		r += 8;
		mvprintw(r, 200, "The winner is : ");
		attron(COLOR_PAIR(curr->c));
		mvprintw(r++, 216, "%s", curr->name);
		attroff(COLOR_PAIR(curr->c));
		mvprintw(++r, 200, "Press %s %s", (core->t) ? "any key" : "ESC", \
			"to exit");
	}
	attroff(COLOR_PAIR(4) | A_BOLD);
	refresh();
	pthread_mutex_unlock(&core->m);
}

void	ft_init_colorset(void)
{
	init_pair(1, TITLE_FG, TITLE_BG);
	init_pair(2, BORDER_L_FG, BORDER_L_BG);
	init_pair(3, BORDER_R_FG, BORDER_R_BG);
	init_pair(4, DEFAULT_FG, DEFAULT_BG);
	init_pair(20, BOT_A_FG, BOT_BG);
	init_pair(21, BOT_B_FG, BOT_BG);
	init_pair(22, BOT_C_FG, BOT_BG);
	init_pair(23, BOT_D_FG, BOT_BG);
	init_pair(30, CAR_FG, BOT_A_FG);
	init_pair(31, CAR_FG, BOT_B_FG);
	init_pair(32, CAR_FG, BOT_C_FG);
	init_pair(33, CAR_FG, BOT_D_FG);
}

void	ft_init_border_left(t_border *border)
{
	border->height = 67;
	border->width = 196;
	border->starty = 1;
	border->startx = 0;
}

void	ft_init_border_right(t_border *border)
{
	border->height = 67;
	border->width = 56;
	border->starty = 1;
	border->startx = 197;
}

void	ft_create_border(t_border *border, t_core *core)
{
	int		x;
	int		y;
	int		w;
	int		h;

	pthread_mutex_lock(&core->m);
	x = border->startx;
	y = border->starty;
	w = border->width;
	h = border->height;
	mvaddch(y, x, BORDER_TL);
	mvaddch(y, x + w, BORDER_TR);
	mvaddch(y + h, x, BORDER_BL);
	mvaddch(y + h, x + w, BORDER_BR);
	mvhline(y, x + 1, BORDER_TS, w - 1);
	mvhline(y + h, x + 1, BORDER_BS, w - 1);
	mvvline(y + 1, x, BORDER_LS, h - 1);
	mvvline(y + 1, x + w, BORDER_RS, h - 1);
	pthread_mutex_unlock(&core->m);
}

void	ft_fill_screen(t_core *core)
{
	t_border	border_left;
	t_border	border_right;

	ft_init_border_left(&border_left);
	ft_init_border_right(&border_right);
	pthread_mutex_lock(&core->m);
	attron(COLOR_PAIR(1) | A_BOLD);
	mvprintw(0, 120, "C O R E W A R");
	attroff(COLOR_PAIR(1));
	pthread_mutex_unlock(&core->m);
	attron(COLOR_PAIR(2) | A_REVERSE);
	ft_create_border(&border_left, core);
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(3));
	ft_create_border(&border_right, core);
	attroff(COLOR_PAIR(3) | A_REVERSE);
	pthread_mutex_lock(&core->m);
	attron(COLOR_PAIR(4));
	mvprintw(32, 89, "MAKE PEACE NOT WAR");
	mvprintw(33, 85, "PRESS ANY KEY TO CONTINUE");
	attroff(COLOR_PAIR(4) | A_BOLD);
	refresh();
	pthread_mutex_unlock(&core->m);
}

void	*ft_promo_audio(void *ptr)
{
	if (!ptr)
		ft_play_sound("Track.wav");
	pthread_exit(NULL);
	return (NULL);
}

void	ft_init_win(t_core *core)
{
	pthread_t	thread_promo;

	initscr();
	if (LINES < 69 || COLS < 254)
	{
		endwin();
		ft_printf("Resize window to min %d cols and %d rows. Currently %d cols "
			"and %d rows\n", 254, 69, COLS, LINES);
		exit(0);
	}
	if (has_colors() == FALSE)
	{
		endwin();
		ft_printf("Your terminal does not support color\n");
		exit(0);
	}
	start_color();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	pthread_create(&thread_promo, NULL, ft_promo_audio, NULL);
	pthread_detach(thread_promo);
	ft_init_colorset();
	ft_fill_screen(core);
}

void	ft_win_half(t_core *core, t_champ *curr, int i, int *r)
{
	pthread_mutex_lock(&core->m);
	attron(COLOR_PAIR(4) | A_BOLD);
	mvprintw(32, 89, "%18s", "");
	mvprintw(33, 85, "%25s", "");
	mvprintw(3, 200, "** RUNNING **");
	mvprintw(5, 200, "Cycles/second limit : %d", 10);
	mvprintw(8, 200, "Cycle : %d", core->cycle);
	mvprintw(10, 200, "Processes : %d", core->qt_car);
	mvprintw(12, 200, "Speed: %dx", 100000 / core->t);
	while (i++ < core->qt_champ)
	{
		mvprintw(*r, 200, "Player %d : ", curr->id);
		attron(COLOR_PAIR(curr->c));
		mvprintw((*r)++, 210 + ft_count_dig(curr->id), "%s", curr->name);
		attroff(COLOR_PAIR(curr->c));
		mvprintw(*r, 202, "Last live : ");
		mvprintw((*r)++, 214, "%21d", curr->last_live);
		mvprintw(*r, 202, "Lives in current period : ");
		mvprintw(*r, 228, "%7d", curr->s_live);
		*r += 2;
		curr = curr->next;
	}
	attroff(COLOR_PAIR(4) | A_BOLD);
	pthread_mutex_unlock(&core->m);
}

void	ft_fill_win(t_core *core, int r)
{
	ft_win_half(core, core->champs, 0, &r);
	attron(COLOR_PAIR(4) | A_BOLD);
	pthread_mutex_lock(&core->m);
	mvprintw(r++, 200, "Live breakdown for current period :");
	attroff(A_BOLD);
	mvprintw(r++, 200, "[--------------------------------------------------]");
	attron(A_BOLD);
	mvprintw(++r, 200, "Live breakdown for last period :");
	attroff(A_BOLD);
	mvprintw(++r, 200, "[--------------------------------------------------]");
	core->l = r;
	attron(A_BOLD);
	r++;
	mvprintw(++r, 200, "CYCLE_TO_DIE : %d", core->c_to_die);
	r++;
	mvprintw(++r, 200, "CYCLE_DELTA : %d", CYCLE_DELTA);
	r++;
	mvprintw(++r, 200, "NBR_LIVE : %d", NBR_LIVE);
	r++;
	mvprintw(++r, 200, "MAX_CHECKS : %d", MAX_CHECKS);
	attroff(COLOR_PAIR(4));
	attroff(A_BOLD);
	pthread_mutex_unlock(&core->m);
}

void	ft_init_screen(t_core *core, int i, int r, int c)
{
	pthread_t	thread_resize_win;

	pthread_mutex_init(&core->m, NULL);
	ft_init_win(core);
	pthread_create(&thread_resize_win, NULL, ft_resize_win, (void*)core);
	pthread_detach(thread_resize_win);
	getch();
	ft_fill_win(core, 14);
	pthread_mutex_lock(&core->m);
	while (i < MEM_SIZE)
	{
		mvprintw(r, c, "%02x ", core->arena[i]);
		i++;
		if (i % 64 == 0)
		{
			c = 3;
			r++;
		}
		else
			c += 3;
	}
	pthread_mutex_unlock(&core->m);
}

int		ft_init_sdl(char *src, SDL_AudioSpec *spec, Uint32 *len, Uint8 **buf)
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0)
		return (1);
	if (SDL_LoadWAV(src, spec, buf, len) == NULL)
	{
		SDL_Quit();
		return (1);
	}
	return (0);
}

void	ft_play_callback(void *udata, Uint8 *stream, int len)
{
	Uint32	tmp;

	tmp = len;
	if (g_len == 0)
		return ;
	else if (tmp > g_len)
		len = g_len;
	if (udata)
		udata = NULL;
	SDL_memset(stream, 0, len);
	SDL_memcpy(stream, g_buf, len);
	SDL_MixAudio(stream, g_buf, len, SDL_MIX_MAXVOLUME / 2);
	g_len -= len;
	g_buf += len;
}

void	ft_play_sound(char *src)
{
	SDL_AudioSpec	spec;
	Uint32			len;
	Uint8			*buf;

	if (ft_init_sdl(src, &spec, &len, &buf))
		return ;
	spec.callback = ft_play_callback;
	spec.userdata = NULL;
	if (SDL_OpenAudio(&spec, NULL) < 0)
		return ;
	g_len = len;
	g_buf = buf;
	SDL_PauseAudio(0);
	while (g_len > 0)
		SDL_Delay(500);
	SDL_CloseAudio();
	SDL_FreeWAV(buf);
	SDL_Quit();
}

void	ft_set_rc(int *r, int *c, int pos)
{
	*r = 3 + ((pos % MEM_SIZE) / 64) % 64;
	*c = 3 + (3 * ((pos % MEM_SIZE) % 64)) % 192;
}

void	ft_vcars_on(t_core *core, t_car *car, int ag, int pos)
{
	int		r;
	int		c;
	t_champ	*champ;

	pthread_mutex_lock(&core->m);
	champ = ft_get_champ(core, car->id);
	if (pos < 0)
		pos = MEM_SIZE + pos;
	car->rp = pos;
	car->sw = 1;
	attron(COLOR_PAIR(champ->c) | A_BOLD);
	ft_set_rc(&r, &c, pos);
	mvprintw(r, c, "%02x", (unsigned char)(ag >> 24));
	ft_memset(core->a + (pos % MEM_SIZE), champ->c, 1);
	ft_set_rc(&r, &c, ++pos);
	mvprintw(r, c, "%02x", (unsigned char)(ag >> 16 & 255));
	ft_memset(core->a + (pos % MEM_SIZE), champ->c, 1);
	ft_set_rc(&r, &c, ++pos);
	mvprintw(r, c, "%02x", (unsigned char)(ag >> 8 & 255));
	ft_memset(core->a + (pos % MEM_SIZE), champ->c, 1);
	ft_set_rc(&r, &c, ++pos);
	mvprintw(r, c, "%02x", (unsigned char)(ag & 255));
	ft_memset(core->a + (pos % MEM_SIZE), champ->c, 1);
	attroff(COLOR_PAIR(champ->c) | A_BOLD);
	pthread_mutex_unlock(&core->m);
}

void	ft_vcars_off(t_core *core, t_car *tmp)
{
	int		pos;
	int		r;
	int		c;

	pthread_mutex_lock(&core->m);
	tmp->sw = 0;
	pos = tmp->rp;
	ft_set_rc(&r, &c, pos);
	attron(COLOR_PAIR(core->a[pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", (unsigned char)(core->arena[pos % MEM_SIZE]));
	attroff(COLOR_PAIR(core->a[pos % MEM_SIZE]));
	ft_set_rc(&r, &c, ++pos);
	attron(COLOR_PAIR(core->a[pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", (unsigned char)(core->arena[pos % MEM_SIZE]));
	attroff(COLOR_PAIR(core->a[pos % MEM_SIZE]));
	ft_set_rc(&r, &c, ++pos);
	attron(COLOR_PAIR(core->a[pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", (unsigned char)(core->arena[pos % MEM_SIZE]));
	attroff(COLOR_PAIR(core->a[pos % MEM_SIZE]));
	ft_set_rc(&r, &c, ++pos);
	attron(COLOR_PAIR(core->a[pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", (unsigned char)(core->arena[pos % MEM_SIZE]));
	attroff(COLOR_PAIR(core->a[pos % MEM_SIZE]));
	pthread_mutex_unlock(&core->m);
}

void	ft_vcars_check(t_core *core, t_car *tmp)
{
	int		r;
	int		c;

	if (tmp->sw)
		ft_vcars_off(core, tmp);
	pthread_mutex_lock(&core->m);
	ft_set_rc(&r, &c, tmp->pos);
	attron(COLOR_PAIR(core->a[tmp->pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", core->arena[tmp->pos % MEM_SIZE]);
	attroff(COLOR_PAIR(core->a[tmp->pos % MEM_SIZE]));
	pthread_mutex_unlock(&core->m);
}

void	ft_vcars_norev(t_core *core, t_car *car)
{
	int		r;
	int		c;

	pthread_mutex_lock(&core->m);
	r = 3 + ((car->pos % MEM_SIZE) / 64) % 64;
	c = 3 + (3 * ((car->pos % MEM_SIZE) % 64)) % 192;
	attron(COLOR_PAIR(core->a[car->pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", core->arena[car->pos % MEM_SIZE]);
	attroff(COLOR_PAIR(core->a[car->pos % MEM_SIZE]));
	pthread_mutex_unlock(&core->m);
}

void	ft_vcars_rev(t_core *core, t_car *car)
{
	int		r;
	int		c;
	t_champ	*champ;

	pthread_mutex_lock(&core->m);
	champ = ft_get_champ(core, car->id);
	r = 3 + ((car->pos % MEM_SIZE) / 64) % 64;
	c = 3 + (3 * ((car->pos % MEM_SIZE) % 64)) % 192;
	if (core->arena[car->pos % MEM_SIZE] == 1 \
		&& car->id == ft_read_4(core, car->pos % MEM_SIZE))
		attron(A_BOLD | COLOR_PAIR(champ->cc));
	else
		attron(A_REVERSE | COLOR_PAIR(core->a[car->pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", core->arena[car->pos % MEM_SIZE]);
	if (core->arena[car->pos % MEM_SIZE] == 1 \
		&& car->id == ft_read_4(core, car->pos % MEM_SIZE))
		attroff(A_BOLD | COLOR_PAIR(champ->cc));
	else
		attroff(A_REVERSE | COLOR_PAIR(core->a[car->pos % MEM_SIZE]));
	refresh();
	pthread_mutex_unlock(&core->m);
}

void	ft_champ_visual(t_core *core, t_champ *tmp, int shift)
{
	unsigned int	i;
	unsigned int	r;
	unsigned int	c;

	pthread_mutex_lock(&core->m);
	attron(COLOR_PAIR(tmp->c));
	i = 0;
	r = 3 + (shift / 64);
	c = 3 + 3 * (shift % 64);
	while (i < tmp->size)
	{
		mvprintw(r, c, "%02x", tmp->code[i]);
		if ((1 + i + shift % 64) % 64 == 0 && !(i == 0 && shift == 0))
		{
			c = 3;
			r++;
		}
		else
			c += 3;
		i++;
	}
	attroff(COLOR_PAIR(tmp->c));
	ft_memset(core->a + shift, tmp->c, tmp->size);
	refresh();
	pthread_mutex_unlock(&core->m);
}

void	ft_vcars_fork(t_core *core, t_car *car, int pos)
{
	t_champ	*champ;
	int		r;
	int		c;

	pthread_mutex_lock(&core->m);
	champ = ft_get_champ(core, car->id);
	r = 3 + ((pos % MEM_SIZE) / 64) % 64;
	c = 3 + (3 * ((pos % MEM_SIZE) % 64)) % 192;
	attron(COLOR_PAIR(champ->c) | A_REVERSE);
	mvprintw(r, c, "%02x", core->arena[pos]);
	attroff(COLOR_PAIR(champ->c) | A_REVERSE);
	pthread_mutex_unlock(&core->m);
}
