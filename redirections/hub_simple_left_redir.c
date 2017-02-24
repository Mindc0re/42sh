/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_simple_left_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:32:32 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

static int		simple_left(char *filename)
{
	FT_INIT(int, new_fd, 0);
	if ((new_fd = open(filename, O_RDONLY, 0600)) == -1)
	{
		ft_error(filename);
		return (0);
	}
	if (g_shell.left_redir_fd != -1)
		close(g_shell.left_redir_fd);
	g_shell.left_redir_fd = new_fd;
	return (1);
}

static int		get_left_redirs(char *line)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, filename, NULL);
	if (!ft_strchr(line, '<'))
		return (0);
	while (line[i])
	{
		if (line[i] == '<')
		{
			if (line[i + 1] == '<')
				return (0);
			i += line[i + 1] == ' ' ? 2 : 1;
			if (!(filename = get_filename(line, i)))
				return (0);
			if (!simple_left(filename))
				return (0);
			free(filename);
		}
		i++;
	}
	return (1);
}

static char		*delete_left_redirs_str(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	while (str && i < (int)ft_strlen(str))
	{
		if (str[i] == '<')
		{
			j = i;
			while (str[j] && str[j - 1] != '<')
				j++;
			if (str[j] == ' ')
				j++;
			while (str[j] && str[j] != ' ')
				j++;
			tmp2 = ft_strsub(str, i, j - i);
			tmp = ft_str_replace(str, tmp2, "");
			ft_strdel(&tmp2);
			ft_strdel(&str);
			str = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		i++;
	}
	return (str);
}

char			*hub_simple_left_redir(char *line)
{
	FT_INIT(int, ret_redir, get_left_redirs(line));
	FT_INIT(char *, ret, NULL);
	if (!ret_redir)
		return (line);
	else
	{
		ret = delete_left_redirs_str(ft_strdup(line));
		ft_strdel(&line);
	}
	return (ret);
}
