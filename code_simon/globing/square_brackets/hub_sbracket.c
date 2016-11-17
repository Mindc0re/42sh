/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_sbracket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:01:41 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/16 11:01:41 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int				fill_bracket_tabs(char *line, t_glob *glob) // Fonction qui choisit la méthode de remplissage de notre tableau de caractères (glob->sbracket->bracket)
{
	FT_INIT(char *, tmp_error, NULL);
	bracket_pushback(&glob->sbracket);
	tmp_error = handle_categories(line, glob);
	free(line);
	line = ft_strdup(tmp_error);
	free(tmp_error);
	if (!check_rng(line))
	{
		tmp_error = ft_strjoin("42sh: no matches found: ", glob->command);
		ft_putendl_fd(tmp_error, 2);
		free(tmp_error);
		return (0);
	}
	glob->sbracket->content = fill_mix(line);
	return (1);
}

void			hub_sbracket(t_glob *glob) // Gère les différents cas de figure, cf commentaires dans le .h ac les definitions des macros
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, NULL);
	while (g_shell.line[i])
	{
		if (g_shell.line[i] == '[' && g_shell.line[i + 1]
			&& g_shell.line[i + 1] == '!')
		{
			tmp = ft_strsub(g_shell.line, i,
				next_bracket(g_shell.line, '[', i) + 1);
			fill_bracket_tabs(ft_strdup(tmp), glob);
			i += next_bracket(g_shell.line, '[', i);
			free(tmp);
			printf("\033[32mRet = %s\033[0m\n", glob->sbracket->content);
		}
		else if (g_shell.line[i] == '[' && g_shell.line[i + 1]
			&& g_shell.line[i + 1] != '!')
		{
			tmp = ft_strsub(g_shell.line, i,
				next_bracket(g_shell.line, '[', i) + 1);
			fill_bracket_tabs(ft_strdup(tmp), glob);
			i += next_bracket(g_shell.line, '[', i);
			free(tmp);
			printf("\033[32mRet = %s\033[0m\n", glob->sbracket->content);
		}
		i++;
	}
}
