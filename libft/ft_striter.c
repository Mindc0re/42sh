/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:51:11 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	unsigned int i;

	i = 0;
	if (s != NULL && f != NULL)
	{
		while (s[i])
		{
			f(&s[i]);
			i++;
		}
	}
}
