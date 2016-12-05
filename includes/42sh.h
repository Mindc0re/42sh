/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/07 18:51:39 by jthevene          #+#    #+#             */
/*   Updated: 2016/12/05 16:21:40 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _42SH_H
# define _42SH_H

# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <curses.h>
# include "../libft/includes/libft.h"

# define K_PRINT   1 //caractere imprimable
# define K_ESCAPE  2
# define K_UP      3
# define K_DOWN    4
# define K_RIGHT   5
# define K_LEFT    6
# define K_DEL	   7
# define K_BACKSP  8
# define K_RETURN  9
# define K_UNKNOWN 10

typedef struct 		s_lst
{
	void			*content;
	struct s_lst	*prev;
	struct s_lst	*next;
	int 			number;
} 					t_lst;

typedef struct		s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}					t_var;

typedef struct		s_shell
{
	char			*oldpwd;
	t_var			*vars;//contenu de ENV
	int 			cursor_x;
	int 			nb_rows; // 0 = premiere ligne de la commande en cours d'edition
	struct winsize	*win;
	int				running;
	t_lst			*hist;
	int 			hist_fd;
	t_lst			*last_hist; //derniere ligne de l'historique
	t_lst			*end_hist_file; //derniere ligne du fichier history
	int 			nav_hist; // 0 = pas encore navigué dans l'historique
	struct termios	my_termios;
	struct termios	t_back;
	char			*current_line; //ligne en cours d'edition
	char			buf[8]; //pas sur qu'on en ait besoin en fait
	char			*line; // VARIABLE SIMON
}					t_shell;

t_shell		g_shell;

/*
** CATCH_KEY
*/
int					readkey(void);
/*
** CURSOR_MOVE
*/
void				ft_cursor_right(int i);
void				ft_cursor_left(int i);
void				cursor_next_line(void);
/*
** GET_PATH
*/
t_list				*get_dir_content(char *dir);
char				*ft_strpathjoin(const char *s1, const char *s2);
/*
** HISTORY
*/
void				get_hist(void);
void				ft_newhist(char *line);
void				navigation_hist(int arrow);
void				ft_history(int i);
/*
** HISTORY2
*/
void				clear_history_list(void);
void				delete_line_history(int i);
void				show_hist_list(void);
void				update_history_file(void);
/*
** INIT
*/
int					init_all(void);
void				init_hist(void);
/*
** LINE_EDITION
*/
void				fill_current_line(char c);
/*
** MAIN
*/
void				display_prompt(void);
/*
** PRINT_LINE
*/
void				clean_line(void);
void				print_line(int i);
/*
** RETURN_KEY
*/
void				return_key(void);
void				backspace_key(void);
/*
** SIGNAL
*/
void				ft_signal(void);
/*
** TERMIOS
*/
int					init_termios(struct termios my_termios);
void				ft_reset_termios(struct termios t_back);
/*
** VAR
*/
char				*get_var(t_shell *g_shell, char *n_var);
t_var				*new_var(char *v_name, char *v_value);
void				ft_varappend(t_var *new_element);

#endif
