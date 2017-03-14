/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:45:52 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		print_tokens(t_token *token)
{
	int		i;

	i = 1;
	printf("\n***TOKEN_LIST***\n");
	while (token)
	{
		printf("TOKEN %d\n", i);
		printf("type : (%d)\n", token->type);
		printf("lexeme : (%s)\n", token->lexeme);
		token = token->next;
		i++;
	}
}

t_token		*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->lexeme = NULL;
	token->next = NULL;
	return (token);
}

int			fd_redir(t_token *token, char *line, int pos)
{
	FT_INIT(int, i, 1);
	FT_INIT(int, x, pos);
	while (ft_isdigit((unsigned char)line[pos + i]))
		i++;
	if (line[pos + i] == '>')
	{
		pos = pos + i + 1;
		token->type = MORE;
		add_lexeme(token, line, pos, x);
		return (pos);
	}
	return (pos);
}
