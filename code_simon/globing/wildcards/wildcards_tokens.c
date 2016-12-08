/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 21:03:02 by sgaudin           #+#    #+#             */
/*   Updated: 2016/12/07 21:03:03 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int			g_no_token(char *str, t_glob *glob)
{
	if (!bracket_pushback(&glob->args))
		return (0);
	printf("NO TOKEN\n");
	glob->args->content = ft_strdup(str);
	return (1);
}

int			only_qmark(char *str, t_glob *glob)
{
	FT_INIT(int, len, ft_strlen(str));
	printf("LEN ARG QMARK : %d\n", len);
	if (glob)
		return (1);
	return (0);
}

int			only_star(char *str, t_glob *glob)
{
	printf("STAR\n");
	if (str && glob)
		return (1);
	return (0);
}

int			only_cbrkt(char *str, t_glob *glob)
{
	FT_INIT(int, len, get_len_token(str));
	FT_INIT(char *, path, get_cmd_path(str));
	FT_INIT(t_list *, files, get_dir_content(path));
	FT_INIT(int, i, -1);
	hub_sbracket(glob, str);
	while (files)
	{
		if (ft_strlen(files->content) == len)
		{
			while (++i < len)
			{
				if (ft_strchr(files->content[i], glob->sbracket->content))
					glob->sbracket = glob->sbracket->next ? glob->sbracket->next : glob->sbracket;
				else
					break ;
			}
			if (i == len)
			{
				pushback_content(&glob->args, ft_strdup(files->content));
				printf("Création d'argument : %s\n", glob->args->content);
			}
			rewind_tbracket(&glob->sbracket);
			i = -1;
		}
		if (!files->next)
			break ;
		files = files->next;
	}
	return (0);
}

int			mix_token(char *str, t_glob *glob)
{
	FT_INIT(int, len, get_len_token(str));
	FT_INIT(char *, path, get_cmd_path(str));
	printf("LEN ARG MIX: %d\n", len);
	printf("PATH = %s\n", path);
	free(path);
	if (glob)
		return (1);
	return (0);
}