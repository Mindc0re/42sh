/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 14:01:40 by jules             #+#    #+#             */
/*   Updated: 2017/02/02 21:01:39 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

static char 		*get_str_to_replace(char *event)
{
	FT_INIT(char*, tmp, NULL);
	FT_INIT(char*, str_to_replace, NULL);
	FT_INIT(int, i, 1);
	tmp = ft_strdup(ft_strchr(event, '!'));
	while (tmp && tmp[i] && tmp[i] != ' ' && tmp[i] != '!')
		i++;
	i = tmp[1] == '!' ? 2 : i;
	str_to_replace = ft_strsub(tmp, 0, i);
	ft_strdel(&tmp);
	return (str_to_replace);
}

static char 		*get_target(char *str_to_replace)
{
	FT_INIT(char*, target, NULL);
	FT_INIT(int, i, 0);
	FT_INIT(int, start, 0);
	FT_INIT(int, end, 0);
	while (str_to_replace && str_to_replace[i] && str_to_replace[i] == '!')
		i++;
	start = i;
	end = ft_strlen(str_to_replace) - 1;
	target = ft_strsub(str_to_replace, start, end);
	return (target);
}

static int 		exec_match(char *event, char *str_to_replace, char *replace_by)
{
	FT_INIT(char*, tmp, NULL);
	tmp = ft_str_replace(event, str_to_replace, replace_by);
	if (!replace_by)
	{
		ft_printf("\n42sh: %s: event not found", str_to_replace);
		free(str_to_replace ? str_to_replace : NULL);
		return (0);
	}
	else
		ft_strdel(&replace_by);
	free(str_to_replace ? str_to_replace : NULL);
	ft_bzero(g_shell.current_line, g_shell.len);
	ft_strcpy(g_shell.current_line, tmp);
	free(tmp ? tmp : NULL);
	if (ft_strchr(g_shell.current_line, '!'))
		return (history_event(g_shell.current_line));
	ft_printf("\n%s\n", g_shell.current_line);
	return (1);
}

int	history_event(char *event)
{
	FT_INIT(char*, str_to_replace, get_str_to_replace(event));
	FT_INIT(char*, replace_by, NULL);
	FT_INIT(char*, target, get_target(str_to_replace));
	FT_INIT(int, digit, 0);
	FT_INIT(int, alnum, 0);
	while (target && target[digit] && 
		(ft_isdigit(target[digit]) || target[0] == '-'))
		digit++;
	while (target && target[alnum] && ft_isalnum(target[alnum]))
		alnum++;
	if (str_to_replace && !ft_strcmp(str_to_replace, "!!"))
		replace_by = event_n(-1, str_to_replace);
	else if (digit && digit == (int)ft_strlen(target))
		replace_by = event_n(ft_atoi(target), str_to_replace);
	else if (alnum && alnum == (int)ft_strlen(target))
		replace_by = event_str(target, str_to_replace);
	ft_strdel(&target);
	return (exec_match(event, str_to_replace, replace_by));
}
