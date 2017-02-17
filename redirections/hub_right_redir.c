/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_right_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 18:33:17 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/14 18:33:17 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static int			push_right_redir(char *filename, int fd_in, int type
									, t_fdlist **fdlist)
{
	FT_INIT(t_fdlist, *tmp, NULL);
	FT_INIT(t_fdlist, *new, NULL);
	if (!(*fdlist))
	{
		if (!((*fdlist) = new_node_fdlist(filename, fd_in, type)))
			return (0);
	}
	else
	{
		if (!(new = new_node_fdlist(filename, fd_in, type)))
			return (0);
		while ((*fdlist)->next)
			(*fdlist) = (*fdlist)->next;
		tmp = (*fdlist);
		(*fdlist)->next = new;
		new->prev = tmp;
	}
	return (1);
}

static int			check_right_redir(char *line, int i, t_fdlist **fdlist)
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
	i += line[i + 1] == ' ' ? 2 : 1;
	if (!(filename = get_filename(line, i)))
		return (0);
	if (!(push_right_redir(filename, fd_in, type, fdlist)))
	{
		ft_strdel(&filename);
		return (0);
	}
	ft_strdel(&filename);
	return (1);
}

static t_fdlist		*get_right_redirs(char *line)
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
				free_fdlist(&fdlist);
				return (NULL);
			}
			if (line[i + 1] && line[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (fdlist);
}

char				*hub_right_redir(char *line)
{
	FT_INIT(t_fdlist, *fdlist, get_right_redirs(line));
	FT_INIT(char *, ret, NULL);
	if (!fdlist)
		return (line);
	else
	{
		while (fdlist->prev)
			fdlist = fdlist->prev;
		printf("PRINTING FDLIST NODES\n\n");
		while (fdlist->next)
		{
			printf("~***\ntype = %d\nfd_in = %d\nfd_file = %d\nfilename = %s\n***~\n", fdlist->type, fdlist->fd_in, fdlist->fd_file, fdlist->filename);
			fdlist = fdlist->next;
		}
		printf("~***\ntype = %d\nfd_in = %d\nfd_file = %d\nfilename = %s\n***~\n", fdlist->type, fdlist->fd_in, fdlist->fd_file, fdlist->filename);
		printf("\nENDING OF PRINTING FDLIST NODES\n");
		printf("\nNOW REPLACING STR\n");
		ret = delete_redirs_str(ft_strdup(line));
		ft_strdel(&line);
		printf("REDIRS DELETED : %s\n\n", ret);
	}
	free_fdlist(&fdlist);
	return (ret);
}