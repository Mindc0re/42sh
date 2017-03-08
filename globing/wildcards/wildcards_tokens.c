/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:11 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int			only_qmark(char *str, int star, t_glob *g)
{
	g->f_path = get_cmd_path(str);
	g->l_path = get_cmd_last_path(str);
	FT_INIT(t_lst *, files, get_dir_content(!g->f_path ? "./" : g->f_path));
	FT_INIT(size_t, len, get_len_token(str));
	while (files->next && files->next->content)
	{
		if (star == TRUE && ft_strlen(files->content) >= len)
			push_content_path(&g->args, ft_strdup(files->content), g);
		else if (star == FALSE && len == ft_strlen(files->content))
			push_content_path(&g->args, ft_strdup(files->content), g);
		files = files->next;
	}
	if (star == TRUE && ft_strlen(files->content) >= len)
		push_content_path(&g->args, ft_strdup(files->content), g);
	else if (star == FALSE && len == ft_strlen(files->content))
		push_content_path(&g->args, ft_strdup(files->content), g);
	ft_lst_free(&files);
	free_double_str(&g->f_path, &g->l_path);
	return (0);
}

void		only_cbrkt2(int i, int len, t_lst *f, t_glob *g)
{
	while (++i < len)
	{
		if (ft_strchr(g->sbracket->content, ((char*)f->content)[i]))
			g->sbracket = g->sbracket->next ? g->sbracket->next : g->sbracket;
		else
			break ;
	}
	if (i == len)
		push_content_path(&g->args, ft_strdup(f->content), g);
}

int			only_cbrkt(char *str, t_glob *g)
{
	g->f_path = get_cmd_path(str);
	g->l_path = get_cmd_last_path(str);
	FT_INIT(int, len, get_len_token(str));
	FT_INIT(t_lst *, f, get_dir_content(!g->f_path ? "./" : g->f_path));
	FT_INIT(int, i, -1);
	hub_sbracket(g, str);
	rewind_tbracket(&g->sbracket);
	while (f)
	{
		if ((int)ft_strlen(f->content) == len)
		{
			only_cbrkt2(i, len, f, g);
			rewind_tbracket(&g->sbracket);
			i = -1;
		}
		if (!f->next)
			break ;
		f = f->next;
	}
	free_double_str(&g->f_path, &g->l_path);
	free_tbracket(&g->sbracket);
	ft_lst_free(&f);
	return (0);
}

int			mix_with_star(char *str, t_glob *g)
{
	g->f_path = get_cmd_path(str);
	g->l_path = get_cmd_last_path(str);
	FT_INIT(char *, token, wild_get_token(str));
	FT_INIT(t_lst *, files, get_dir_content(!g->f_path ? "./" : g->f_path));
	hub_sbracket(g, token);
	rewind_tbracket(&g->sbracket);
	while (files)
	{
		if (ft_strcmp(files->content, ".") && ft_strcmp(files->content, ".."))
			check_file(ft_strlen(files->content), token, files->content, &g);
		if (!files->next)
			break ;
		files = files->next;
	}
	if (g->f_path)
		free(g->f_path);
	if (g->l_path)
		free(g->l_path);
	if (token)
		free(token);
	free_tbracket(&g->sbracket);
	ft_lst_free(&files);
	return (0);
}

int			mix_token(char *str, t_glob *g)
{
	g->f_path = get_cmd_path(str);
	g->l_path = get_cmd_last_path(str);
	FT_INIT(char *, token, wild_get_token(str));
	FT_INIT(t_lst *, files, get_dir_content(!g->f_path ? "./" : g->f_path));
	FT_INIT(int, len, get_len_token(token));
	hub_sbracket(g, token);
	rewind_tbracket(&g->sbracket);
	while (files)
	{
		if ((int)ft_strlen(files->content) == len)
			check_file(len, token, files->content, &g);
		rewind_tbracket(&g->sbracket);
		if (!files->next)
			break ;
		files = files->next;
	}
	if (g->f_path)
		free(g->f_path);
	if (g->l_path)
		free(g->l_path);
	if (token)
		free(token);
	free_tbracket(&g->sbracket);
	ft_lst_free(&files);
	return (0);
}
