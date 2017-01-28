/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/07 18:51:39 by jthevene          #+#    #+#             */
/*   Updated: 2017/01/28 15:03:22 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

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
# include <errno.h>
# include "../libft/includes/libft.h"

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
** ERROR
*/
void				ft_error(char *str);
void				ft_out_of_range(int i);
/*
** EVENT
*/
char				*event_n(int n);
void				check_pattern_event(char *event);
/*
** FT_HISTORY
*/
void				ft_history_print(t_lst *lst);
void				ft_history(char *nbr);
/*
** FT_HISTORY_OPTIONS
*/
void				clear_history_list(void);
void				delete_line_history(int i);
void				show_hist_list(void);
void				update_history_file(char *filename, int histfilesize);
void				option_p(void);
/*
** GET_PATH
*/
t_lst				*get_dir_content(char *dir);
/*
** HISTORIC
*/
void				get_hist(void);
void				ft_newhist(char *line);
void				put_hist_line(char *content);
void				navigation_hist(int arrow);
/*
** HISTSIZE
*/
void				update_histfilesize(int histfilesize);
void				update_histsize(int histsize);
int 				get_histsize(char *var);
/*
** INIT
*/
int					init_env();
int					init_all(void);
void				init_hist_opt();
void				init_win();
void				init_hist(void);
/*
** LINE_EDITION
*/
void				fill_current_line(char c);
/*
** LST_TOOLS
*/
t_lst				*ft_newlst(char *content);
void				ft_append_lst(t_lst **lst, t_lst *new_elem);
void				ft_print_list_content(t_lst *lst);
void				ft_lst_rewind_n(t_lst **lst, int n);
void				ft_lst_rewind(t_lst **lst);
void				ft_lst_forward(t_lst **lst);
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
** QUESTION_MARK
*/
t_lst 				*qmark_get_matching_content(t_lst *dir_content, char *target);
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
