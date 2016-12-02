/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_clist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 11:53:17 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/18 11:53:18 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"
#define FILS_DE_PUTERIE "ls {a{i,bc{d,e}f{g,h}z,blob},jk{lm{no,p}q{r,s},t}uv}"

static int		touching_brackets(char *str)
{
	FT_INIT(int, i, 0);
	while (str[i])
	{
		if (str[i] == '{')
		{
			i += next_bracket(str, '{', i);
			if (str[i + 1] == '{')
				return (1);
		}
		i++;
	}
	return (0);
}

static int		len_sub(char *str)
{
	return (str[ft_strlen(str) - 1] == '}' ? 1 : 0);
}

static int		start_cbracket(char *str, t_glob *glob)
{
	FT_INIT(int, i, 0);
	while (str[i - 1] != '{')
		i++;
	glob->ext_args = recup_ext_args(str);
	return (i);
}

void			get_patterns(char *str, t_glob *glob)
{
	if (!ft_strchr(str, '{'))
	{
		clist_list_pushback(&glob->cbracket);
		glob->cbracket->list->content = expand_pattern(str, glob);
		printf("New pattern created : %s\n", glob->cbracket->list->content);
	}
	else
		i_algo_imbricated(ft_strdup(str), glob);
	glob->lastb_count = 1;
}

int				fill_clist(char *line, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(int, i, start_cbracket(line, glob));
	if (touching_brackets(line))
	{
		i_algo_imbricated(ft_strdup(line), glob);
		return (1);
	}
	while (line[i])
	{
		if (next_comma(line, i) == -1)
		{
			if (is_bracket_in_exp(line, i) > 1)
				tmp = ft_strsub(line, i, ft_strlen(line) - i - len_sub(line));
			else
				tmp = ft_strsub(line, i, end_bracket(line, i));
			printf("next_comma 1 = %s\n", tmp);
			get_patterns(tmp, glob);
			free(tmp);
			break ;
		}
		else
		{
			tmp = ft_strsub(line, i, next_comma(line, i));
			i += next_comma(line, i);
		}
		printf("next_comma 2 = %s\n", tmp);
		get_patterns(tmp, glob);
		free(tmp);
		i++;
	}
	print_clist(&glob->cbracket);
	return (1);
}
