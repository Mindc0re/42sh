/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 11:43:43 by sgaudin           #+#    #+#             */
/*   Updated: 2016/12/07 09:22:51 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

static int				verif_tokens(char *str)
{
	FT_INIT(int, nb, 0);
	if (ft_strchr(str, '[') && !ft_strchr(str, ']'))
		return (0);
	else if (!count_brackets(str, '['))
		return (0);
	else
		nb++;
	if (ft_strchr(str, '{') && !ft_strchr(str, '}'))
		return (0);
	else if (!count_brackets(str, '{'))
		return (0);
	else
		nb++;
	if (ft_strchr(str, '*') || ft_strchr(str, '?'))
		nb++;
	if (!nb)
		return (0);
	return (1);
}

static int				get_command(char *str, t_glob *glob) // Fonction qui recupere la commande pour le message d'erreur
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	while (str[i] && str[i] != ' ')
		i++;
	i++;
	j = i;
	while (str[j] && str[j] != ' ')
		j++;
	if (!(glob->command = ft_strnew(j - i)))
		return (-1);
	j = 0;
	while (str[i] && str[i] != ' ')
	{
		glob->command[j] = str[i];
		j++;
		i++;
	}
	return (0);
}

t_glob					*init_glob(void)
{
	t_glob				*glob;

	glob = (t_glob *)malloc(sizeof(t_glob));
	glob->sbracket = NULL;
	glob->cbracket = NULL;
	glob->tmp_c = NULL;
	glob->c_touch = FALSE;
	glob->lastb_count = 1;
	glob->exp = NULL;
	ft_bzero(glob->upper, 27);
	ft_bzero(glob->lower, 27);
	ft_bzero(glob->alpha, 53);
	ft_bzero(glob->digit, 11);
	ft_bzero(glob->alnum, 63);
	ft_bzero(glob->space, 7);
	ft_bzero(glob->graph, 95);
	ft_bzero(glob->print, 96);
	ft_bzero(glob->punct, 33);
	ft_bzero(glob->cntrl, 34);
	ft_bzero(glob->xdigit, 17);
	init_tabs1(glob, 0, 0); // Les 3 fonctions init_tabs servent à remplir les tableaux pour [[:upper:]], [[:xdigit:]] etc...
	init_tabs2(glob);
	init_tabs3(glob);
	return (glob);
}

/*
void			free_glob(t_glob *glob)
{
	if (glob->sbracket)
		free_tbracket(&glob->sbracket);
	if (glob->cbracket)
		free_tclist(&glob->cbracket);
	if (glob->command)
		free(glob->command);
	free(glob);
}
*/

int						glob_parser(void)
{
	static t_glob		*glob = NULL;

	if (!g_shell.line)
		return (0);
	if (!verif_tokens(g_shell.line))
		return (0);
	if (g_shell.line[0] == '@')
	{
		glob = !glob ? init_glob() : glob;
		get_command(g_shell.line, glob);
		if (ft_strchr(g_shell.line, '{'))
			if (!hub_cbracket(glob))
				return (0);
		hub_final(glob);
		if (glob->args)
		{
			rewind_tbracket(&glob->args);
			while (glob->args->next)
			{
				printf("Arg : %s\n", glob->args->content);
				glob->args = glob->args->next;
			}
			printf("Arg : %s\n", glob->args->content);
			free_tbracket(&glob->args);
		}
		if (glob->command)
			free(glob->command);
	}
	return (1);
}
