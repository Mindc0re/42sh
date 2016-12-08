/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 10:41:51 by jules             #+#    #+#             */
/*   Updated: 2016/11/08 17:23:08 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void 	get_win_val()
{
	// Sauvegarde de la taille actuelle de la fenetre
	g_shell.prev_win->ws_row = g_shell.win->ws_row;
	g_shell.prev_win->ws_col = g_shell.win->ws_col;
	g_shell.prev_win->ws_xpixel = g_shell.win->ws_xpixel;
	g_shell.prev_win->ws_ypixel = g_shell.win->ws_ypixel;
	// Sauvegarde de la position actuelle du curseur
	g_shell.prev_cursor_x = g_shell.cursor_x;
	g_shell.prev_cursor_2d_x = g_shell.cursor_2d_x;
	g_shell.prev_cursor_2d_y = g_shell.cursor_2d_y;
	// Sauvegarde de la taille de la ligne
	g_shell.prev_line_size = g_shell.line_size;
	g_shell.prev_line_2d_y = g_shell.line_2d_y;
	g_shell.prev_line_2d_x = g_shell.line_2d_x;
}


void 	monitoring()
{
	FT_INIT(int, nb_line, g_shell.line_2d_y + 1);
	while (nb_line)
	{
		ft_putstr("\n");
		nb_line--;
	}
	printf("g_shell.cursor_2d_x =%d\ng_shell.cursor_2d_y =%d\ng_shell,line_2d_x =%d\ng_shell.line_2d_y =%d,\nwin_size =%d\n, cursor_x =%d,\nlen_size =%d\n",
	 g_shell.cursor_2d_x, g_shell.cursor_2d_y, g_shell.line_2d_x, g_shell.line_2d_y, g_shell.win->ws_col, g_shell.cursor_x, g_shell.line_size);
	nb_line = g_shell.line_2d_y + 1;
	while (nb_line)
	{
		ft_putstr("\n");
		nb_line--;
	}	
}


void 	reset_cursor_pos()
{
	FT_INIT(int, dif_x, g_shell.line_size - g_shell.cursor_x);
	g_shell.cursor_x = g_shell.line_size;
	while (dif_x > 0)
	{
	 	arrow_moove_left();
		dif_x--;
	}
}

int 	set_cursor_start(int len)
{
	if (len < g_shell.line_2d_y)
	{
		ft_putstr("\n");
		tputs(tgetstr("rc", NULL), 1, ft_putchar_int);
		tputs(tgetstr("up", NULL), 1, ft_putchar_int); // scroll up
		tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
		tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
		ft_putstr("\033[32m$> \033[0m");
		tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
		len = g_shell.line_2d_y;
	}
	else
	{
		tputs(tgetstr("rc", NULL), 1, ft_putchar_int);
		tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
	}
	return (len);
}

int 	set_cursor_start2(int len, int diff_win) // Permet de gerer les modification de taille du terminal, echec et non fonctionnel
{
	tputs(tgetstr("rc", NULL), 1, ft_putchar_int);
	if (!diff_win)
		return (len);
	if (diff_win > 0) // Agrandissement
	{
		if (g_shell.prev_line_2d_y == 1 && !g_shell.line_2d_y 
			&& g_shell.line_2d_x + 1 == g_shell.win->ws_col && !g_shell.prev_line_2d_x)
			tputs(tgetstr("up", NULL), 1, ft_putchar_int);
	}
	else if (diff_win < 0)
	{
		if (g_shell.prev_line_2d_y < g_shell.line_2d_y)
		{
//			tputs(tgetstr("sf", NULL), 1, ft_putchar_int);
//			ft_putstr("\n");
//			ft_putstr("\ntest\n");
//			usleep(300000);
		}
	}

	if (diff_win != 0)
	{
		tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
		tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
		ft_putstr("\033[32m$> \033[0m");
		tputs(tgetstr("sc", NULL), 1, ft_putchar_int);		
	}
	return (len);
}

void 	display_with_select(char *line)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, start_select, -3);
	FT_INIT(int, end_select, -3);
	start_select += g_shell.start_select < g_shell.end_select ? g_shell.start_select : g_shell.end_select;
	end_select += g_shell.end_select > g_shell.start_select ? g_shell.end_select : g_shell.start_select;
	while (line[i])
	{
		if (i == start_select)
		{
			ft_putstr("\033[47m");
			ft_putstr("\033[30m");
		}
		ft_putchar(line[i]);
		if (i == end_select || (i == end_select - 1 && end_select == g_shell.line_size - 3))
		{
			ft_putstr("\033[0m");
			ft_putstr("\033[0m");
		}
		i++;
	}
}

void	clean_line()
{
	int i;
	
	i = ft_strlen(g_shell.current_line) + 3;
	g_shell.nb_rows = 1;
	if (i > g_shell.win->ws_col)
	{
		g_shell.nb_rows = i / g_shell.win->ws_col;
		if ((i % g_shell.win->ws_col) != 0)
			g_shell.nb_rows++;
	}
	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	tputs(tgetstr("dl", NULL), 1, ft_putchar_int);
	while (g_shell.nb_rows-- > 1)
	{
		tputs(tgetstr("dl", NULL), 1, ft_putchar_int);
		tputs(tgetstr("up", NULL), 1, ft_putchar_int);
	}
}

void	print_line(int i)
{
	set_2d_line_val();
	set_2d_cursor_val();
	static int len = 0;
//	FT_INIT(int, diff_win, g_shell.win->ws_col - g_shell.prev_win->ws_col);
//	monitoring();
	if (i)
		i--;
	len = set_cursor_start(len);
	if (!g_shell.start_select && !g_shell.end_select)
		ft_putstr(g_shell.current_line);
	else
		display_with_select(g_shell.current_line);
	if (!g_shell.line_2d_x)	
		ft_putstr("\n");
	reset_cursor_pos();
	get_win_val();
	return ;
}