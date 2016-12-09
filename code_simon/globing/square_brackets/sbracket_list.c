/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sbracket_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:40:25 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/04 14:40:29 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int					bracket_pushback(t_bracket **list)
{
	FT_INIT(t_bracket, *tmp, NULL);
	FT_INIT(t_bracket, *new, NULL);
	if (!(*list))
	{
		if (!((*list) = (t_bracket *)malloc(sizeof(t_bracket))))
			return (0);
		(*list)->prev =  NULL;
		(*list)->next = NULL;
		(*list)->content = NULL;
	}
	else
	{
		if (!(new = (t_bracket *)malloc(sizeof(t_bracket))))
			return (0);
		new->next = NULL;
		new->content = NULL;
		while ((*list)->next)
			(*list) = (*list)->next;
		tmp = (*list);
		(*list)->next = new;
		new->prev = tmp;
		(*list) = (*list)->next;
	}
	return (1);
}

int				pushback_content(t_bracket **list, char *content)
{
	if (!bracket_pushback(list))
		return (0);
	(*list)->content = content;
	return (1);
}

void			rewind_tbracket(t_bracket **list)
{
	if (*list)
	{
		while ((*list)->prev)
		{
//			printf("LIST PREV CONTENT = %s\n", (*list)->prev->content);
//			printf("LIST CONTENT = %s\n", (*list)->content);
			(*list) = (*list)->prev;
		}
	}
}

void			free_tbracket(t_bracket **list)
{
	FT_INIT(t_bracket *, tmp, NULL);
	while ((*list)->prev)
		(*list) = (*list)->prev;
	while ((*list)->next)
	{
		if ((*list)->content)
			free((*list)->content);
		tmp = (*list);
		(*list) = (*list)->next;
		free(tmp);
	}
	if ((*list)->content)
		free((*list)->content);
	tmp = (*list);
	(*list) = NULL;
	free(tmp);
}