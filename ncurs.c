#include "ncurs.h"

//Uint32		g_len;
//Uint8		*g_buf;

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

typedef struct _win_border_struct {
        chtype  ls, rs, ts, bs,
                tl, tr, bl, br;
} WIN_BORDER;

typedef struct _WIN_struct {
        int startx, starty;
        int height, width;
        WIN_BORDER border;
} WIN;


void init_win_params(WIN *p_win, int h, int w, int sy, int sx);
void print_win_params(WIN *p_win);
void init_win_params2(WIN *p_win, int h, int w, int sy, int sx);
void create_box(WIN *win, bool flag, t_core *core);

int	init_help(void)
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

int	get_response(void)
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

void	p_man(size_t *i, size_t j, char c, char *str)
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

int			p_help(size_t i, size_t j, int fd, char c)
{
	int		row_col[2];
	int		y_x[2];
	char	*str;

	if (init_help())
		return (6);
	while (get_next_line(fd, &str) > 0)
	{
		getmaxyx(stdscr, row_col[0], row_col[1]);
		getyx(stdscr, y_x[0], y_x[1]);
		if (y_x[0] == (row_col[0] - 1))
		{
			if (get_response())
				return (0);
		}
		i = 0;
		j = ft_strlen(str);
		while (i < j)
			p_man(&i, j, '\0', str);
		printw("\n");
	}
	read(0, &c, 1);
	endwin();
	return (0);
}

void    *myThreadFun4(void *ptr)
{
	t_core *p;
    int sw = 0;

    p = (t_core *)ptr;
    if (!ptr)
    {
        ; // ? Fatal error sound
        // play("Track1.wav");
    }
    while (!sw)
    {
        if (LINES < 69 || COLS < 254)
        {
		    pthread_mutex_lock(&(p)->m);

            clear();
            refresh();
            endwin();
  			system("reset");
  			// SDL_Quit(); // ? Check
            ft_printf("'corewar' shut down unexpectedly. Resize window to min 254 cols and 69 rows. Currently %d cols and %d rows.\n", COLS, LINES);
            exit(122);

		    pthread_mutex_unlock(&(p)->m);
        }
    }
    // pthread_exit(NULL);
    // SDL_Quit();
    return (NULL);
}

void	do_win(void)
{
	WINDOW *my_win;
	int startx, starty, width, height;
	int ch;

	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	// cbreak();


	height = 3;
	width = 10;
	starty = (LINES - height) / 2;
	startx = (COLS - width) / 2;
	printw("Press F1 to exit");
	refresh();
	my_win = create_newwin(height, width, starty, startx);
	while ((ch = getch()) != KEY_F(1))
	{
		switch(ch)
		{
			case KEY_LEFT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty, --startx);
				break;
			case KEY_RIGHT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty, ++startx);
				break;
			case KEY_UP:
				destroy_win(my_win);
				my_win = create_newwin(height, width, --starty, startx);
				break;
			case KEY_DOWN:
				destroy_win(my_win);
				my_win = create_newwin(height, width, ++starty, startx);
				break;
		}
	}
	endwin();
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);
	
	wrefresh(local_win);

	return (local_win);
}

void	destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}

int		cnt_dig(int nbr)
{
	int cnt;


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

void	do_last(t_core *core)
{
	int i, r, c, j, k, d;
	double s;
	// int i, r, c;
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

	/*
	refresh();
	*/
    
    pthread_mutex_unlock(&core->m);
}

void	do_ncurs(t_core *core)
{

	//	int ch;
	int i, r, c, j, k, d;
	double s;
	// int i, r, c;
	t_champ *curr;
	static int sw = 0;

	if (!core)
	{
		sw = 0;
		return ;
	}
	if (sw == 0)
	{
		// i = 0;
		// r = 3;
		// c = 3;
		// while (i < MEM_SIZE)
		// {
		// 	mvprintw(r, c, "%02x ", core->arena[i]);
		// 	i++;
		// 	if (i % 64 == 0)
		// 	{
		// 		c = 3;
		// 		r++;
		// 	}
		// 	else
		// 		c += 3;
		// }
		sw = 1;
	}
   
    pthread_mutex_lock(&core->m);

	attron(A_BOLD);
	mvprintw(3, 200, "** RUNNING **");
	// mvprintw(5, 200, "Cycles/second limit : %d", 50);
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
	// attron(A_BOLD);
	r++;
	mvprintw(++r, 215, "%-10d", core->c_to_die);
	// mvprintw(++r, 200, "CYCLE_TO_DIE : %d", core->c_to_die);
	// r++;
	// ++r;// mvprintw(++r, 200, "CYCLE_DELTA : %d", CYCLE_DELTA);
	// r++;
	// ++r;// mvprintw(++r, 200, "NBR_LIVE : %d", NBR_LIVE);
	// r++;
	// ++r;// mvprintw(++r, 200, "MAX_CHECKS : %d", MAX_CHECKS);
	attroff(COLOR_PAIR(4));
	attroff(A_BOLD);
	refresh();
    
    pthread_mutex_unlock(&core->m);

	// cbreak();
	// keypad(stdscr, TRUE);
	// noecho();
	/*
	while((ch = getch()) != KEY_F(1))
	{
		switch(ch)
		{
			case KEY_LEFT:
				create_box(&win, FALSE);
				--win.startx;
				create_box(&win, TRUE);
				break;
			case KEY_RIGHT:
				create_box(&win, FALSE);
				++win.startx;
				create_box(&win, TRUE);
				break;
			case KEY_UP:
				create_box(&win, FALSE);
				--win.starty;
				create_box(&win, TRUE);
				break;
			case KEY_DOWN:
				create_box(&win, FALSE);
				++win.starty;
				create_box(&win, TRUE);
				break;
		}
	}
	endwin();
	*/
}

void	init_ncurs(t_core *core)
{
	WIN win;
	WIN win2;
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

	init_win_params(&win, 67, 196, 1, 0);
	//	print_win_params(&win);
	init_win_params2(&win2, 67, 56, 1, 197);

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
	create_box(&win, TRUE, core);
	attroff(COLOR_PAIR(2));

	attron(COLOR_PAIR(3));
	create_box(&win2, FALSE, core);
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

pthread_create(&thread_id3, NULL, myThreadFun4, (void*)core);
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
		mvprintw(r++, 210 + cnt_dig(curr->id), "%s", curr->name);
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

	/*
	refresh();
	*/
    
    pthread_mutex_unlock(&core->m);

// getch();
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
	// usleep(1000000);

	/*
	refresh();
	*/

    pthread_mutex_unlock(&core->m);

	/*
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        endwin();
        exit(11);
    }

	SDL_AudioSpec want, have;

	SDL_memset(&want, 0, sizeof(want)); // or SDL_zero(want)
	want.freq = 48000;
	want.format = AUDIO_F32;
	want.channels = 2;
	want.samples = 4096;
	want.callback = MyAudioCallback; // you wrote this function elsewhere.

	if (SDL_OpenAudio(&want, &have) < 0) {
	    SDL_Log("Failed to open audio: %s", SDL_GetError());
	} else {
	    if (have.format != want.format) {
	        SDL_Log("We didn't get Float32 audio format.");
	    }
	    SDL_PauseAudio(0); // start audio playing.
	    SDL_Delay(5000); // let the audio callback play some sound for 5 seconds.
	    SDL_CloseAudio();
	}


	system("afplay Track1.mp3&");
    SDL_Quit();
	*/
	// sound("Track1.wav");
    // getch();
}

//void	callback(void *udata, Uint8 *stream, int len)
//{
//	Uint32 tmp;
//
//	tmp = len;
//	if (g_len == 0)
//		return ;
//	else if (tmp > g_len)
//		len = g_len;
//	if (udata)
//		udata = NULL;
//	SDL_memset(stream, 0, len);
//	SDL_memcpy(stream, g_buf, len);
//	SDL_MixAudio(stream, g_buf, len, SDL_MIX_MAXVOLUME / 2);
//	g_len -= len;
//	g_buf += len;
//}
//
//void	play(char *src)
//{
//	SDL_AudioSpec	spec;
//	Uint32			len;
//	Uint8			*buf;
//
//	if (SDL_Init(SDL_INIT_AUDIO) != 0)
//	{
//		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
//		return ;
//	}
//	if (SDL_LoadWAV(src, &spec, &buf, &len) == NULL)
//	{
//		SDL_Log("Unable to load file '%s': %s", src, SDL_GetError());
//		return ;
//	}
//	spec.callback = callback;
//	spec.userdata = NULL;
//	if (SDL_OpenAudio(&spec, NULL) < 0)
//	{
//		SDL_Log("Unable to open audio: %s", SDL_GetError());
//		return ;
//	}
//	g_len = len;
//	g_buf = buf;
//	SDL_PauseAudio(0);
//	while (g_len > 0)
//		SDL_Delay(500);
//	SDL_CloseAudio();
//	SDL_FreeWAV(buf);
//}

void init_win_params(WIN *p_win, int h, int w, int sy, int sx)
{
        p_win->height = h;
        p_win->width = w;
		// p_win->starty = (LINES - p_win->height)/2;
		p_win->starty = sy;
		// p_win->startx = (COLS - p_win->width)/2;
		p_win->startx = sx;
        p_win->border.ls = ACS_VLINE;
        p_win->border.rs = ACS_VLINE;
        p_win->border.ts = ACS_HLINE;
        p_win->border.bs = ACS_HLINE;
        p_win->border.tl = ACS_ULCORNER;
        p_win->border.tr = ACS_URCORNER;
        p_win->border.bl = ACS_LLCORNER;
        p_win->border.br = ACS_LRCORNER;
}

void init_win_params2(WIN *p_win, int h, int w, int sy, int sx)
{
	p_win->height = h;
	p_win->width = w;
	//		p_win->starty = (LINES - p_win->height)/2;
	p_win->starty = sy;
	//		p_win->startx = (COLS - p_win->width)/2;
	p_win->startx = sx;
	p_win->border.ls = ACS_VLINE;
	p_win->border.rs = ACS_VLINE;
	p_win->border.ts = ACS_HLINE;
	p_win->border.bs = ACS_HLINE;
	p_win->border.tl = ACS_TTEE;
	p_win->border.tr = ACS_URCORNER;
	p_win->border.bl = ACS_BTEE;
	p_win->border.br = ACS_LRCORNER;
}

void print_win_params(WIN *p_win)
{
	if (p_win)
	{
		;
	}
#ifdef _DEBUG
	mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty, p_win->width, p_win->height);
	refresh();
#endif
}


void create_box(WIN *p_win, bool flag, t_core *core)
{
	// int i, j;
	int x, y, w, h;

    pthread_mutex_lock(&core->m);

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	if( flag == TRUE)
	{
		p_win->border.ls = ACS_VLINE;
		p_win->border.rs = ACS_VLINE;
		p_win->border.ts = ACS_HLINE;
		p_win->border.bs = ACS_HLINE;
		p_win->border.tl = ACS_ULCORNER;
		p_win->border.tr = ACS_URCORNER;
		p_win->border.bl = ACS_LLCORNER;
		p_win->border.br = ACS_LRCORNER;

		mvaddch(y, x, p_win->border.tl);
		mvaddch(y, x + w, p_win->border.tr);
		mvaddch(y + h, x, p_win->border.bl);
		mvaddch(y + h, x + w, p_win->border.br);
		mvhline(y, x + 1, p_win->border.ts, w - 1);
		mvhline(y + h, x + 1, p_win->border.bs, w - 1);
		mvvline(y + 1, x, p_win->border.ls, h - 1);
		mvvline(y + 1, x + w, p_win->border.rs, h - 1);
	}
	else
		// for(j = y; j <= y + h; ++j)
			// for(i = x; i <= x + w; ++i)
				// mvaddch(j, i, ' ');
	{
		p_win->border.ls = ACS_VLINE;
		p_win->border.rs = ACS_VLINE;
		p_win->border.ts = ACS_HLINE;
		p_win->border.bs = ACS_HLINE;
		p_win->border.tl = ACS_ULCORNER;
		p_win->border.tr = ACS_URCORNER;
		p_win->border.bl = ACS_LLCORNER;
		p_win->border.br = ACS_LRCORNER;

		mvaddch(y, x, p_win->border.tl);
		mvaddch(y, x + w, p_win->border.tr);
		mvaddch(y + h, x, p_win->border.bl);
		mvaddch(y + h, x + w, p_win->border.br);
		mvhline(y, x + 1, p_win->border.ts, w - 1);
		mvhline(y + h, x + 1, p_win->border.bs, w - 1);
		mvvline(y + 1, x, p_win->border.ls, h - 1);
		mvvline(y + 1, x + w, p_win->border.rs, h - 1);
	}

	/*
	refresh();
	*/
    
    pthread_mutex_unlock(&core->m);
}

void	do_acs(void)
{
	initscr();
	printw("Upper left corner "); addch(ACS_ULCORNER); printw("\n");
	printw("Lower left corner "); addch(ACS_LLCORNER); printw("\n");
	printw("Lower right corner "); addch(ACS_LRCORNER); printw("\n");
	printw("Tee pointing right "); addch(ACS_LTEE); printw("\n");
	printw("Tee pointing left "); addch(ACS_RTEE); printw("\n");
	printw("Tee pointing up "); addch(ACS_BTEE); printw("\n");
	printw("Tee pointing down "); addch(ACS_TTEE); printw("\n");
	printw("Horizontal line "); addch(ACS_HLINE); printw("\n");
	printw("Vertical line "); addch(ACS_VLINE); printw("\n");
	printw("Large Plus or cross over "); addch(ACS_PLUS); printw("\n");
	printw("Scan Line 1 "); addch(ACS_S1); printw("\n");
	printw("Scan Line 3 "); addch(ACS_S3); printw("\n");
	printw("Scan Line 7 "); addch(ACS_S7); printw("\n");
	printw("Scan Line 9 "); addch(ACS_S9); printw("\n");
	printw("Diamond "); addch(ACS_DIAMOND); printw("\n");
	printw("Checker board (stipple) "); addch(ACS_CKBOARD); printw("\n");
	printw("Degree Symbol "); addch(ACS_DEGREE); printw("\n");
	printw("Plus/Minus Symbol "); addch(ACS_PLMINUS); printw("\n");
	printw("Bullet "); addch(ACS_BULLET); printw("\n");
	printw("Arrow Pointing Left "); addch(ACS_LARROW); printw("\n");
	printw("Arrow Pointing Right "); addch(ACS_RARROW); printw("\n");
	printw("Arrow Pointing Down "); addch(ACS_DARROW); printw("\n");
	printw("Arrow Pointing Up "); addch(ACS_UARROW); printw("\n");
	printw("Board of squares "); addch(ACS_BOARD); printw("\n");
	printw("Lantern Symbol "); addch(ACS_LANTERN); printw("\n");
	printw("Solid Square Block "); addch(ACS_BLOCK); printw("\n");
	printw("Less/Equal sign "); addch(ACS_LEQUAL); printw("\n");
	printw("Greater/Equal sign "); addch(ACS_GEQUAL); printw("\n");
	printw("Pi "); addch(ACS_PI); printw("\n");
	printw("Not equal "); addch(ACS_NEQUAL); printw("\n");
	printw("UK pound sign "); addch(ACS_STERLING); printw("\n");
	refresh();
	getch();
	endwin();
}