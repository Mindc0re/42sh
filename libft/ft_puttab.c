/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 12:14:03 by jthevene          #+#    #+#             */
/*   Updated: 2016/04/24 12:25:57 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puttab(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		ft_putendl(array[i]);
		i++;
	}
}
