/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:08:06 by vjean             #+#    #+#             */
/*   Updated: 2023/05/19 15:11:15 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	ft_free_null(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	ft_free_tab(void **tab)
{
	int	i;

	if (tab)
	{
		i = -1;
		while (tab[++i])
			ft_free_null(tab[i]);
		ft_free_null(tab);
	}
}