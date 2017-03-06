/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:32:45 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	reset_line(void)
{
	move_cursor_n_to_direction(g_shell.line_size, 1);
	if (g_shell.current_line)
		ft_strdel(&g_shell.current_line);
	g_shell.current_line = NULL;
	g_shell.nav_hist = 0;
	free_hist_opt();
	init_hist_opt();
}

void	return_key(void)
{
	go_to_end();
	FT_INIT(int, add_hist, 0);
	if (ft_strlen(g_shell.current_line))
	{
		if (g_shell.current_line && ft_strchr(g_shell.current_line, '!'))
			add_hist += history_event(g_shell.current_line);
		ft_putchar('\n');
		g_shell.result_exec = -99;
		g_shell.all_results = -99;
		lexer_parser(ft_strdup(g_shell.current_line));
		ft_putchar('\n');
		reset_line();
	}
	else
		ft_putchar(10);
	g_shell.curr_hist = g_shell.hist;
	g_shell.len = 0;
	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
	display_prompt();
}
