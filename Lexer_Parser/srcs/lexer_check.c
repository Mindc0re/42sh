/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:24:18 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/12 15:24:20 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			check_ope(t_token *token, char *line, int pos, int i)
{
	if (ft_isope(line[pos]) == 1)
	{
		token->type = AND;
		i = pos;
		pos = pos + 2;
		add_lexeme(token, line, pos, i);
	}
	else if (ft_isope(line[pos]) == 2)
		pos = left_redir_token(token, line, pos, i);
	else if (ft_isope(line[pos]) == 3)
		pos = right_redir_token(token, line, pos, i);
	else if (ft_isope(line[pos]) == 4)
		pos = pipe_or_token(token, line, pos, i);
	else if (ft_isope(line[pos]) == 5)
	{
		token->type = SEMICOLON;
		i = pos;
		pos++;
		add_lexeme(token, line, pos, i);
	}
	return (pos);
}

int			left_redir_token(t_token *token, char *line, int pos, int i)
{
	if (line[pos + 1] == '<')
	{
		token->type = DLESS;
		i = pos;
		pos = pos + 2;
		add_lexeme(token, line, pos, i);
	}
	else
	{
		token->type = LESS;
		i = pos;
		pos++;
		add_lexeme(token, line, pos, i);
	}
	return (pos);
}

int			right_redir_token(t_token *token, char *line, int pos, int i)
{
	if (line[pos + 1] == '>')
	{
		token->type = DMORE;
		i = pos;
		pos = pos + 2;
		add_lexeme(token, line, pos, i);
	}
	else
	{
		token->type = MORE;
		i = pos;
		pos++;
		add_lexeme(token, line, pos, i);
	}
	return (pos);
}

int			pipe_or_token(t_token *token, char *line, int pos, int i)
{
	if (line[pos + 1] == '|')
	{
		token->type = OR;
		i = pos;
		pos = pos + 2;
		add_lexeme(token, line, pos, i);
	}
	else
	{
		token->type = PIPE;
		i = pos;
		pos++;
		add_lexeme(token, line, pos, i);
	}
	return (pos);
}

int			ft_isprintnotope(char c)
{
	if (ft_isope(c) >= 1)
		return (0);
	else if (c == ' ')
		return (0);
	else if (c == '\t')
		return (0);
	else if (c == '\n')
		return (0);
	else if (c == '\"')
		return (0);
	else if (c == '\'')
		return (0);
	else if (ft_isprint(c) == 1)
		return (1);
	return (0);
}
