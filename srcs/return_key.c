/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 13:12:22 by jules             #+#    #+#             */
/*   Updated: 2016/12/06 16:06:18 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

void	return_key(void)
{ 
	t_list	*dir_content;

	dir_content = NULL;
	if (dir_content = get_dir_content(g_shell.current_line))
		ft_print_list_content(dir_content);
	else
		ft_putendl("FAILED");
	// INSEREZ VOS FONCTIONS AU DESSUS
	if (g_shell.current_line)
	{
		clean_line();
		display_prompt();
		ft_putstr(g_shell.current_line);
		if (g_shell.hist->content)
			ft_newhist(g_shell.current_line);
		else
			g_shell.hist->content = ft_strdup(g_shell.current_line);
			g_shell.hist->number++;
		g_shell.current_line = NULL;
		g_shell.nav_hist = 0;
	}
	ft_putchar(10);
	display_prompt();
}

void	backspace_key(void)
{
	char	*tmp;
	int 	len;

	if (g_shell.current_line)
	{
		if ((len = ft_strlen(g_shell.current_line)) > 0)
		{
			tmp = ft_strdup(g_shell.current_line);
			if (!(g_shell.current_line = (char*)malloc(sizeof(char) * len)))
				return;
			g_shell.current_line = ft_strncpy(g_shell.current_line, tmp, len - 1);
			ft_cursor_left(1);
			print_line(len - 1);
		}
	}
}
