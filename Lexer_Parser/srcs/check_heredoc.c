#include "../includes/sh.h"

void	check_for_hdoc(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp->next)
	{
		if (tmp->type == DLESS)
			replace_hdoc(tmp->next);
		tmp = tmp->next;
	}
}

void	replace_hdoc(t_token *token)
{
	char *myline;
	char *heredoc;

	heredoc = ft_strdup("");
	ft_strdel(&g_shell.prompt);
	myline = prompt_dquote("> ");
	if (ft_strcmp(myline, token->lexeme) != 0)
		heredoc = ft_strjoinchar(heredoc, myline, '\n');
	while (ft_strcmp(myline, token->lexeme) != 0)
	{
		ft_strdel(&g_shell.prompt);
		ft_putstr("\n");
		myline = prompt_dquote("> ");
		if (ft_strcmp(myline, token->lexeme) != 0)
			heredoc = ft_strjoinchar(heredoc, myline, '\n');
	}
	ft_strdel(&(token->lexeme));
	token->lexeme = ft_strdup(heredoc);
	free(myline);
	free(heredoc);
}