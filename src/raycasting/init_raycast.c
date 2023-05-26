/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:34:18 by vjean             #+#    #+#             */
/*   Updated: 2023/05/26 14:48:03 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

/*		FOUR FUNCTIONS		*/

/**
* @param data blabla
*/
void	init_player_pos(t_parse *data)
{
	if (data->map->player == 'N')
	{
		data->ray->dir_playerX = 0;
		data->ray->dir_playerY = -1;
	}
	else if (data->map->player == 'S')
	{
		data->ray->dir_playerX = 0;
		data->ray->dir_playerY = 1;
	}
	else if (data->map->player == 'W')
	{
		data->ray->dir_playerX = -1;
		data->ray->dir_playerY = 0;
	}
	else if (data->map->player == 'E')
	{
		data->ray->dir_playerX = 1;
		data->ray->dir_playerY = 0;
	}
}

void	init_plane(t_parse *data)
{
	data->ray->plane_X = data->ray->dir_playerY * -0.66;
	if (data->ray->dir_playerX != 0)
		data->ray->plane_Y = data->ray->dir_playerX * 0.66;
	else
		data->ray->plane_Y = 0.0;
}

void	init_struct(t_parse *data)
{
	data->ray->hit = 0;
	data->ray->map_x = (int)data->ray->pos_X;
	data->ray->map_y = (int)data->ray->pos_Y;
}

void	setup_struct(t_parse *data)
{
	data->ray = malloc(sizeof(t_raycast));
	data->image = mlx_new_image(data->mlx, W, H);
	data->ray->pos_X = data->map->player_x + 0.5;
	data->ray->pos_Y = data->map->player_y + 0.5;
	data->ray->map_x = (int)data->ray->pos_X;
	data->ray->map_y = (int)data->ray->pos_Y;
	data->ray->move_speed = 0.15;
	init_player_pos(data);
	init_plane(data);
}