/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_final.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 09:37:08 by sgaudin           #+#    #+#             */
/*   Updated: 2016/12/07 09:37:09 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

static int	is_only_token(char token, char *str)
{
	FT_INIT(int, i, 0);
	if (!ft_strchr(str, token))
		return (0);
	while (str[i])
	{
		if (str[i] != token)
			return (0);
		if (str[i] == '[')
			i += next_bracket(str, '[', i);
		i++;
	}
	return (1);
}

int			only_star(char *str, t_glob *glob)
{
	FT_INIT(char *, path, get_cmd_path(str));
	FT_INIT(t_list *, files, get_dir_content(path));
	while (files)
	{
		pushback_content(&glob->args, ft_strdup(files->content));
		printf("Création d'argument : %s\n", glob->args->content);
		if (!files->next)
			break ;
		files = files->next;
	}
	return (0);
}

int			g_parse_expr(char *str, t_glob *glob)
{
//	printf("g_parse_expr = %s\n", str);
	if (!ft_strchr(str, '?') && !ft_strchr(str, '[') && !ft_strchr(str, '*'))
		return (g_no_token(str, glob));
	else if (is_only_token('?', str))
		return (only_qmark(str, glob));
	else if (is_only_token('[', str))
		return (only_cbrkt(str, glob));
	else if (is_only_token('*', str))
		return (only_star(str, glob));
	else if (ft_strchr(str, '*'))
		return (mix_with_star(str, glob));
	else
		return (mix_token(str, glob));
}

void		hub_final(t_glob *glob) // Hub final du traitement globing
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, NULL);
	while (g_shell.line && g_shell.line[i] != ' ')
		i++;
	i++;
	if (glob->cbracket)
		rewind_tbracket(&glob->cbracket->list);
	while (g_shell.line[i])
	{
		tmp = next_expr(g_shell.line, i);
		i += ft_strlen(tmp);
//		printf("Hub final = %s\n", tmp);
		if (ft_strchr(tmp, '{') && ft_strchr(tmp, '}') && glob->cbracket)
		{
			while (glob->cbracket->list->next)
			{
				g_parse_expr(glob->cbracket->list->content, glob);
				glob->cbracket->list = glob->cbracket->list->next;
			}
			g_parse_expr(glob->cbracket->list->content, glob);
			if (glob->cbracket->next)
				glob->cbracket = glob->cbracket->next;
		}
		else
			g_parse_expr(tmp, glob);
		free(tmp);
	}
}