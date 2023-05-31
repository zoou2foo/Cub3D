/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:27:51 by vjean             #+#    #+#             */
/*   Updated: 2023/05/30 14:29:21 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	clear_data(t_parse *data)
{
	int	i;

	i = 0;
	if (data->no != NULL)
		data->no = xfree(data->no);
	if (data->so != NULL)
		data->so = xfree(data->so);
	if (data->we != NULL)
		data->we = xfree(data->we);
	if (data->ea != NULL)
		data->ea = xfree(data->ea);
	data->floor_color = 0;
	data->ceiling_color = 0;
	if (data->map && data->map->map)
	{
		while (data->map->map[i] != NULL)
		{
			data->map->map[i] = xfree(data->map->map[i]);
			i++;
		}
	}
	data->map->map = xfree(data->map->map);
	data->map = xfree(data->map);
}
