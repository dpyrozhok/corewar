#include "ncurs.h"

Uint32		g_len;
Uint8		*g_buf;

typedef struct	s_border_elem
{
		chtype	ls;
		chtype	rs;
		chtype	ts;
		chtype	bs;
		chtype	tl;
		chtype	tr;
		chtype	bl;
		chtype	br;
}				t_border_elem;

typedef struct	s_border
{
		int				startx;
		int				starty;
		int				height;
		int				width;
		t_border_elem	elem;
}				t_border;

void ft_init_border_left (t_border *border);
void ft_init_border_right (t_border *border);
void ft_create_border (t_border *border, t_core *core);

int	ft_init_help(void)
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

int	ft_get_response(void)
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

int	ft_print_help(size_t i, size_t j, int fd, char c)
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
	if (ptr)
	{
		; // ? Fatal error sound
		// ft_play_sound("Track1.wav");
	}
	while (true)
	{
		if (LINES < 69 || COLS < 254)
		{
			pthread_mutex_lock(&(p)->m);

			clear();
			refresh();
			endwin();
			system("reset");
			ft_printf("'corewar' shut down unexpectedly. Resize window to min 254 cols and 69 rows. Currently %d cols and %d rows.\n", COLS, LINES);
			exit(122);

			pthread_mutex_unlock(&(p)->m);
		}
	}
	return (NULL);
}

int	ft_count_dig(int nbr)
{
	int	cnt;

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

void	ft_breakdown(t_core *core)
{
	int i, r, c, j, k, d;
	double s;
	t_champ *curr;

	r = core->l;
	// mvprintw(r, 200, "[");
	i = 0;
	s = 0.0;
	curr = core->champs;
	while (i++ < core->qt_champ)
	{
		s += (double)curr->s_live;
		curr = curr->next;
	}
	c = 0;
	
	pthread_mutex_lock(&core->m);
	
	if (s)
	{

		s = 50/s;
		
		i = 0;
		k = 0;
		curr = core->champs;
		while(i++ < core->qt_champ)
		{
			if (curr->s_live && (s * curr->s_live < 1))
				k++;
			else
				k += (s * curr->s_live);
			curr = curr->next;
		}
		d = 50 - k;

		i = 0;
		curr = core->champs;
		while (i++ < core->qt_champ)	
		{
			if (curr->s_live && (s * curr->s_live < 1))
				k = 1;
			else
				k = s * curr->s_live;
			if (k && d > 0)
			{
				k++;
				d--;
			}
			// if (s)
			j = 0;
			attron(A_BOLD | COLOR_PAIR(curr->c));
			while (j++ < k)
			{
				mvprintw(r, 201+c, "-");
				if (c < 50)
					c++;
			}
			// mvprintw(r, 201+c, "%*s", 50-c, "--------------------------------------------------");
			// if (s)
			attroff(A_BOLD | COLOR_PAIR(curr->c));
			curr = curr->next;
		}
		mvprintw(r, 251, "]");
	}
	else
	{
		attron(COLOR_PAIR(4));
		mvprintw(r, 201, "--------------------------------------------------]");
		attroff(COLOR_PAIR(4));
	}

	if (core->l)
	{
		// pthread_mutex_lock(&core->m);
		attron(COLOR_PAIR(4));
		mvprintw(core->l - 3, 201, "--------------------------------------------------]");
		attroff(COLOR_PAIR(4));
		// pthread_mutex_unlock(&core->m);
	}

	/*
	refresh();
	*/
	
	pthread_mutex_unlock(&core->m);
}

void	ft_draw(t_core *core)
{

	int i, r, c, j, k, d;
	double s;
	t_champ *curr;
	static int sw = 0;

	if (!core)
	{
		sw = 0;
		return ;
	}
	if (sw == 0)
	{
		sw = 1;
	}
   
	pthread_mutex_lock(&core->m);

	attron(A_BOLD);
	mvprintw(3, 200, "** RUNNING **");
	// mvprintw(5, 200, "Cycles/second limit : %d", 50);
	if (core->t)
		mvprintw(5, 222,  "%-10d", 1000000/core->t);
	else
		mvprintw(5, 222, "Stealth");
	mvprintw(8, 200, "Cycle : %d", core->cycle);
	mvprintw(10, 200, "Processes : %-10d", core->qt_car);
	if (core->t != 1000000 && core->t)
	{
		mvprintw(12, 200, "Speed: %dx     ", 100000/core->t);
	}
	else if (core->t)
	{
		mvprintw(12, 200, "Speed: 0.1x     ");
	}
	else
	{
		mvprintw(12, 200, "Speed: Stealth     ");
	}
	r = 14;
	i = 0;
	curr = core->champs;
	while (i++ < core->qt_champ)
	{
		// mvprintw(r, 200, "Player %d : ", curr->id);
		// attron(COLOR_PAIR(curr->c));
		r++;// mvprintw(r++, 210 + cnt_dig(curr->id), "%s", curr->name);
		// attroff(COLOR_PAIR(curr->c));
		// mvprintw(r, 202, "Last live : ");
		mvprintw(r++, 214, "%21d", curr->last_live);
		// mvprintw(r, 202, "Lives in current period : ");
		mvprintw(r, 228, "%7d", curr->s_live);
		r += 2;
		curr = curr->next;
	}

	r++;// mvprintw(r++, 200, "Live breakdown for current period :");
	attroff(A_BOLD);
	// mvprintw(r++, 200, "[--------------------------------------------------]");
	
	// mvprintw(r, 200, "[");
	i = 0;
	s = 0.0;
	curr = core->champs;
	while (i++ < core->qt_champ)
	{
		s += (double)curr->s_live;
		curr = curr->next;
	}
	c = 0;
	if (s)
	{
		s = 50.0/s;
		// mvprintw(2,200,"delta: %f", s);
		
		i = 0;
		k = 0;
		curr = core->champs;
		while(i++ < core->qt_champ)
		{
			if (curr->s_live && (s * curr->s_live < 1))
				k++;
			else
				k += (s * curr->s_live);
				
				// mvprintw(2,225,"mi %d", (int)s*1);
			curr = curr->next;
		}
		// mvprintw(2,225,"sum: %d", k);
		// getch();
		d = 50 - k;
		i = 0;
		curr = core->champs;
		while (i++ < core->qt_champ)	
		{
			if (curr->s_live && (s * curr->s_live < 1))
				k = 1;
			else
				k = s * curr->s_live;
			if (k && d > 0)
			{
				k++;
				d--;
			}
			// if (s)
			j = 0;
			attron(A_BOLD | COLOR_PAIR(curr->c));
			while (j++ < k)
			{
				mvprintw(r, 201+c, "-");
				if (c < 50)
					c++;
			}
			// mvprintw(r, 201+c, "%*s", 50-c, "--------------------------------------------------");
			// if (s)
			attroff(A_BOLD | COLOR_PAIR(curr->c));
			curr = curr->next;
		}
		// r++;
		mvprintw(r++, 201+c, "]");
	}
	else if (sw == 1)
	{
		r++;// mvprintw(r++, 201, "--------------------------------------------------]");
		sw = 2;
	}
	else
		r++;
	if (sw == 2)
	{
		// attron(A_BOLD);
		++r;// mvprintw(++r, 200, "Live breakdown for last period :");
		// attroff(A_BOLD);
		++r;// mvprintw(++r, 200, "[--------------------------------------------------]");
		core->l = r;
		sw = 3;
	}
	else
		r += 2;
	r++;
	attron(A_BOLD);
	mvprintw(++r, 215, "%-10d", core->c_to_die);
	
	if (core->f)
	{
		curr = ft_get_champ(core, core->winner_id);
		r += 8;
		mvprintw(r, 200, "The winner is : ");
		attron(COLOR_PAIR(curr->c));
		mvprintw(r++, 216, "%s", curr->name);
		attroff(COLOR_PAIR(curr->c));
		mvprintw(++r, 200, "Press any key to exit");
	}
	attroff(COLOR_PAIR(4));
	attroff(A_BOLD);
	refresh();
	
	pthread_mutex_unlock(&core->m);

}

void	ft_init_screen(t_core *core)
{
	t_border border_left;
	t_border border_right;
	int i, r, c;
	t_champ *curr;
	pthread_t thread_id3;

	pthread_mutex_init(&core->m, NULL);
	initscr();
	if (LINES < 69 || COLS < 254)
	{
		endwin();
		printf("Resize window to min 254 cols and 69 rows. Currently %d cols and %d rows\n", COLS, LINES);
		exit(0);
	}
	start_color();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	init_pair(1, COLOR_CYAN, COLOR_BLACK); // заголовок
	init_pair(2, COLOR_RED, COLOR_WHITE); // левая рамка
	init_pair(3, COLOR_BLUE, COLOR_WHITE); // правая рамка
	// init_color(COLOR_WHITE, 600, 600, 600); // интенсивность белого
	init_pair(4, COLOR_WHITE, COLOR_BLACK); // белый цвет по дефолту, -1
	init_pair(0, COLOR_WHITE, COLOR_BLACK); // белый цвет по дефолту, -1
	init_pair(20, COLOR_GREEN, COLOR_BLACK); // зеленый бот
	init_pair(21, COLOR_MAGENTA, COLOR_BLACK); // желтый бот
	init_pair(22, COLOR_BLUE, COLOR_BLACK); // синий бот
	init_pair(23, COLOR_RED, COLOR_BLACK); // красный бот
	init_pair(30, COLOR_WHITE, COLOR_GREEN); // команда под кареткой зеленого
	init_pair(31, COLOR_WHITE, COLOR_MAGENTA); // команда под кареткой желтого
	init_pair(32, COLOR_WHITE, COLOR_BLUE); // команда под кареткой синего
	init_pair(33, COLOR_WHITE, COLOR_RED); // команда под каретой красного

	ft_init_border_left(&border_left);
	ft_init_border_right(&border_right);

	pthread_mutex_lock(&core->m);

	attron(COLOR_PAIR(1) | A_BOLD);
	mvprintw(0, (254 - (int)ft_strlen("C O R E W A R")) / 2, "C O R E W A R");
	attroff(COLOR_PAIR(1) | A_BOLD);

	/*
	refresh();
	*/

	pthread_mutex_unlock(&core->m);

	attron(A_REVERSE);
	attron(A_BOLD);

	attron(COLOR_PAIR(2));
	ft_create_border(&border_left, core);
	attroff(COLOR_PAIR(2));

	attron(COLOR_PAIR(3));
	ft_create_border(&border_right, core);
	attroff(COLOR_PAIR(3));
	
	attroff(A_REVERSE);
	
	pthread_mutex_lock(&core->m);
	
	attron(COLOR_PAIR(4));
	// attron(A_BOLD | COLOR_PAIR(3));
	//	mvprintw(3, 3, "00");
	//	attroff(A_BOLD | COLOR_PAIR(3));
	//	attron(COLOR_PAIR(25));
	//	mvprintw(3, 7, "00");
	//	attroff(COLOR_PAIR(25));
	mvprintw(67/2 -1, (196 - (int)ft_strlen("MAKE PEACE NOT WAR"))/2, "MAKE PEACE NOT WAR");
	mvprintw(67/2, (196 - (int)ft_strlen("PRESS ANY KEY TO CONTINUE"))/2, "PRESS ANY KEY TO CONTINUE");
	attroff(A_BOLD);
	refresh();
	
	pthread_mutex_unlock(&core->m);

	pthread_create(&thread_id3, NULL, ft_resize_win, (void*)core);
	pthread_detach(thread_id3);
	getch();
	
	pthread_mutex_lock(&core->m);

	attron(A_BOLD);
	mvprintw(67/2 -1, (196 - (int)ft_strlen("MAKE PEACE NOT WAR"))/2, "                  ");
	mvprintw(67/2, (196 - (int)ft_strlen("PRESS ANY KEY TO CONTINUE"))/2, "                         ");
	mvprintw(67/2, (196 - (int)ft_strlen("* W E L C O M E *"))/2, "* W E L C O M E *");
	// refresh();
	mvprintw(67/2, (196 - (int)ft_strlen("* W E L C O M E *"))/2, "                 ");

	mvprintw(3, 200, "** RUNNING **");
	mvprintw(5, 200, "Cycles/second limit : %d", 50);
	mvprintw(8, 200, "Cycle : %d", core->cycle);
	mvprintw(10, 200, "Processes : %d", core->qt_car);
	mvprintw(12, 200, "Speed: %dx     ", 100000/core->t);

	r = 14;
	i = 0;
	curr = core->champs;
	while (i++ < core->qt_champ)
	{
		mvprintw(r, 200, "Player %d : ", curr->id);
		attron(COLOR_PAIR(curr->c));
		mvprintw(r++, 210 + ft_count_dig(curr->id), "%s", curr->name);
		attroff(COLOR_PAIR(curr->c));
		mvprintw(r, 202, "Last live : ");
		mvprintw(r++, 214, "%21d", curr->last_live);
		mvprintw(r, 202, "Lives in current period : ");
		mvprintw(r, 228, "%7d", curr->s_live);
		r += 2;
		curr = curr->next;
	}
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

	i = 0;
	r = 3;
	c = 3;

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

void	ft_play_callback(void *udata, Uint8 *stream, int len)
{
	Uint32 tmp;

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

	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return ;
	}
	if (SDL_LoadWAV(src, &spec, &buf, &len) == NULL)
	{
		SDL_Log("Unable to load file '%s': %s", src, SDL_GetError());
		SDL_Quit();
		return ;
	}
	spec.callback = ft_play_callback;
	spec.userdata = NULL;
	if (SDL_OpenAudio(&spec, NULL) < 0)
	{
		SDL_Log("Unable to open audio: %s", SDL_GetError());
		return ;
	}
	g_len = len;
	g_buf = buf;
	SDL_PauseAudio(0);
	while (g_len > 0)
		SDL_Delay(500);
	SDL_CloseAudio();
	SDL_FreeWAV(buf);
	SDL_Quit();
}

void ft_init_border_left(t_border *border)
{
	border->height = BORDER_L_HEIGHT;
	border->width = BORDER_L_WIDTH;
	border->starty = BORDER_L_START_Y;
	border->startx = BORDER_L_START_X;
	border->elem.ls = BORDER_LS;
	border->elem.rs = BORDER_RS;
	border->elem.ts = BORDER_TS;
	border->elem.bs = BORDER_BS;
	border->elem.tl = BORDER_TL;
	border->elem.tr = BORDER_TR;
	border->elem.bl = BORDER_BL;
	border->elem.br = BORDER_BR;
}

void ft_init_border_right(t_border *border)
{
	border->height = BORDER_R_HEIGHT;
	border->width = BORDER_R_WIDTH;
	border->starty = BORDER_R_START_Y;
	border->startx = BORDER_R_START_X;
	border->elem.ls = BORDER_LS;
	border->elem.rs = BORDER_RS;
	border->elem.ts = BORDER_TS;
	border->elem.bs = BORDER_BS;
	border->elem.tl = BORDER_TL;
	border->elem.tr = BORDER_TR;
	border->elem.bl = BORDER_BL;
	border->elem.br = BORDER_BR;
}

void ft_create_border(t_border *border, t_core *core)
{
	int	x;
	int	y;
	int	w;
	int	h;

	pthread_mutex_lock(&core->m);
	x = border->startx;
	y = border->starty;
	w = border->width;
	h = border->height;
	mvaddch(y, x, border->elem.tl);
	mvaddch(y, x + w, border->elem.tr);
	mvaddch(y + h, x, border->elem.bl);
	mvaddch(y + h, x + w, border->elem.br);
	mvhline(y, x + 1, border->elem.ts, w - 1);
	mvhline(y + h, x + 1, border->elem.bs, w - 1);
	mvvline(y + 1, x, border->elem.ls, h - 1);
	mvvline(y + 1, x + w, border->elem.rs, h - 1);
	pthread_mutex_unlock(&core->m);
}
