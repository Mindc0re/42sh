/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lexing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 22:25:24 by jules             #+#    #+#             */
/*   Updated: 2017/01/31 17:32:47 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

void	split_line(char *line)
{
	char	**command_tab;
	int		i;

	i = 1;
	command_tab = ft_strsplit(line, ' ');
	i = get_options_str(command_tab);
	get_argument(i, command_tab);
}

void	get_argument(int i, char **array)
{
	int		tab_len;
	int		j;

	tab_len = ft_count_tab(array) - i;
	j = 0;
	if (tab_len > 0)
	{
		g_shell.hist_opt.argument = (char**)malloc(sizeof(char *) * (tab_len + 1));
		if (!g_shell.hist_opt.argument)
			return ;
		while (array[i])
		{
			g_shell.hist_opt.argument[j] = ft_strdup(array[i]);
			i++;
			j++;
		}
		g_shell.hist_opt.argument[j] = NULL;
	}
}

int		get_options_str(char **array)
{
	int		i;

	i = 1;
	if (!array[1])
		return (i);
	while (array[i] && array[i][0] == '-')
	{
		if (i == 1)
			g_shell.hist_opt.options = ft_strdup(array[i]);
		else
			g_shell.hist_opt.options = ft_strjoin(g_shell.hist_opt.options, array[i]);
		i++;
	}
	return (i);
}