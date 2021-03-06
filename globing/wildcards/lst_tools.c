/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:40:12 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:57:45 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

t_lst		*ft_newlst(char *content)
{
	t_lst	*new;

	new = (t_lst*)ft_memalloc(sizeof(t_lst));
	if (new)
	{
		if (!content)
			new->content = NULL;
		else
			new->content = ft_strdup(content);
		new->next = NULL;
		new->prev = NULL;
		new->number = 0;
	}
	return (new);
}

void		ft_append_lst(t_lst **lst, t_lst *new_elem)
{
	t_lst	*tmp;

	if (!*lst)
	{
		*lst = new_elem;
	}
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_elem;
		new_elem->prev = tmp;
		new_elem->number = tmp->number + 1;
	}
}

void		ft_print_list_content(t_lst *lst)
{
	t_lst	*tmp;
	int		i;

	tmp = lst;
	i = 1;
	if (tmp && tmp->content)
	{
		while (tmp->next && tmp->next->content)
		{
			ft_putnbr(i++);
			ft_putstr(" => ");
			ft_putendl(tmp->content);
			tmp = tmp->next;
		}
		ft_putnbr(i++);
		ft_putstr(" => ");
		ft_putendl(tmp->content);
	}
	else
		ft_putendl("Liste NULL");
}

void		ft_lst_rewind(t_lst **lst)
{
	if ((*lst) != NULL)
	{
		while ((*lst)->prev)
			(*lst) = (*lst)->prev;
	}
}

void		ft_lst_free(t_lst **list)
{
	FT_INIT(t_lst *, tmp, NULL);
	if ((*list))
	{
		ft_lst_rewind(list);
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
}
