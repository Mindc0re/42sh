/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:25:03 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/07 13:25:05 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"
#include "../../includes/redir.h"

int 			count_brackets(char *str, char bracket)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, count, 0);
	FT_INIT(int, count_close, 0);
	FT_INIT(char, close, bracket == '[' ? ']' : '}');
	while (str[i])
	{
		if (str[i] == bracket)
			count++;
		else if (str[i] == close)
			count_close++;
		i++;
	}
	if (count != count_close)
		return (0);
	return (1);
}