/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:53:52 by jules             #+#    #+#             */
/*   Updated: 2017/01/30 11:23:13 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

int		check_hist_opt()
{
	int		options;

	options = -1;
	if (g_shell.hist_opt.a)
		options++;
	if (g_shell.hist_opt.r)
		options++;
	if (g_shell.hist_opt.w)
		options++;
	if (g_shell.hist_opt.p)
		options++;
	if (g_shell.hist_opt.s)
		options++;
	if (g_shell.hist_opt.d)
		options++;
	if (options)
		ft_putendl("cannot use more than one of -adrspw");
	return (options);
}

//voir avec le parser_lexer si les arguments sont dans une struct ou envoyé direct en argument
//void	history_hub()
//{
//	if (check_hist_opt())
//		return ;
//	if (g_shell.hist_opt.c)
//		clear_history_list();
//	if (g_shell.hist_opt.d)
//		delete_line_history(/*argument*/);
//	else if (g_shell.hist_opt.a)
//		update_history_file(/*filename*/, get_histsize("HISTSIZE"));
//	else if (g_shell.hist_opt.r)
//		histfile_append(/*filename*/);
//	else if (g_shell.hist_opt.w)
//		update_history_file(/*filename*/, get_histsize("HISTSIZE"));
//	else if (g_shell.hist_opt.s)
//		ft_newhist(/*argument*/);
//}

void	ft_history_print(t_lst *lst)
{
	int 	space;

	space = 5 - ft_nbrlen(lst->number);
	while (space-- > 0)
		ft_putchar(' ');
	ft_putstr(ft_itoa(lst->number));
	ft_putchar(' ');
	ft_putendl(lst->content);
}

void	ft_history(char *nbr)
{
	int 	i;
	t_lst 	*tmp;

	i = 0;
	tmp = g_shell.hist;
	if (ft_strisnum(nbr))
	{
		ft_putendl("numeric argument required");
		return ;
	}
	if (g_shell.hist)
	{
		if (!nbr)
			i = get_histsize("HISTSIZE");
		else
			i = ft_atoi(nbr);
		if (i > 0)
		{
			while (--i > 0 || tmp)
				tmp = tmp->prev;
			while (tmp)
			{
				ft_history_print(tmp);
				tmp = tmp->next;
			}
		}
	}
}