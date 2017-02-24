/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_right_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:32:39 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int				push_right_redir(char *f, int fdin, int type, t_fdlist **flist)
{
	FT_INIT(t_fdlist, *tmp, NULL);
	FT_INIT(t_fdlist, *new, NULL);
	if (!(*flist))
	{
		if (!((*flist) = new_node_fdlist(f, fdin, type)))
			return (0);
	}
	else
	{
		if (!(new = new_node_fdlist(f, fdin, type)))
			return (0);
		while ((*flist)->next)
			(*flist) = (*flist)->next;
		tmp = (*flist);
		(*flist)->next = new;
		new->prev = tmp;
	}
	return (1);
}

static int		check_right_redir(char *line, int i, t_fdlist **fdlist)
{
	FT_INIT(int, type, line[i + 1] && line[i + 1] == '>' ? DOUBLE : SIMPLE);
	FT_INIT(int, fd_in, 0);
	FT_INIT(char *, filename, NULL);
	if (!line[i + 1])
		return (0);
	fd_in = get_fd_in(line, i);
	if (line[i + 1] == '>')
	{
		if (!line[i + 2])
			return (0);
		else
			i += line[i + 2] == ' ' ? 3 : 2;
	}
	else if (line[i + 1] != ' ' && !ft_isalnum(line[i + 1]))
		return (0);
	else
		i += line[i + 1] == ' ' ? 2 : 1;
	if (!(filename = get_filename(line, i))
		|| !(push_right_redir(filename, fd_in, type, fdlist)))
	{
		ft_strdel(&filename);
		return (0);
	}
	ft_strdel(&filename);
	return (1);
}

static t_fdlist	*get_right_redirs(char *line)
{
	FT_INIT(int, i, 0);
	FT_INIT(t_fdlist, *fdlist, NULL);
	if (!ft_strchr(line, '>'))
		return (NULL);
	while (line[i])
	{
		if (line[i] == '>')
		{
			if (!(check_right_redir(line, i, &fdlist)))
			{
				free_fdlist(&fdlist, 1);
				return (NULL);
			}
			if (line[i + 1] && line[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (fdlist);
}

char			*hub_right_redir(char *line)
{
	FT_INIT(t_fdlist, *fdlist, get_right_redirs(line));
	FT_INIT(char *, ret, NULL);
	if (!fdlist)
		return (line);
	else
	{
		ret = delete_right_redirs_str(ft_strdup(line));
		ft_strdel(&line);
	}
	stock_redirs_in_gshell(fdlist);
	free_fdlist(&fdlist, 0);
	return (ret);
}
