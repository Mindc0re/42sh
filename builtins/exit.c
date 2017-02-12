/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 16:49:40 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/12 16:49:43 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

void		ft_exit(void)
{
	go_to_end();
	ft_putstr("\n");
	ft_reset_termios(g_shell.t_back);
	update_history_file(get_histsize("HISTFILESIZE"));
	exit(0);
}
