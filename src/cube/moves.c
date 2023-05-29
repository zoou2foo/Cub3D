/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:21:07 by vjean             #+#    #+#             */
/*   Updated: 2023/05/29 09:05:17 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

void	go_ahead(t_parse *data)
{
	if (data->map->map[(int)data->ray->pos_y][(int)(data->ray->pos_x
		+ data->ray->dir_playerx * data->ray->move_speed)] == '.')
		data->ray->pos_x += data->ray->dir_playerx * data->ray->move_speed;
	if (data->map->map[(int)(data->ray->pos_y + data->ray->dir_playery
			* data->ray->move_speed)][(int)data->ray->pos_x] == '.')
		data->ray->pos_y += data->ray->dir_playery * data->ray->move_speed;
}

void	go_back(t_parse *data)
{
	if (data->map->map[(int)data->ray->pos_y][(int)(data->ray->pos_x
		- data->ray->dir_playerx * data->ray->move_speed)] == '.')
		data->ray->pos_x -= data->ray->dir_playerx * data->ray->move_speed;
	if (data->map->map[(int)(data->ray->pos_y - data->ray->dir_playery
			* data->ray->move_speed)][(int)data->ray->pos_x] == '.')
		data->ray->pos_y -= data->ray->dir_playery * data->ray->move_speed;
}

// gauche et droite
void	go_right(t_parse *data)
{
	if (data->map->map[(int)data->ray->pos_y][(int)(data->ray->pos_x
		+ data->ray->plane_x * data->ray->move_speed)] == '.')
		data->ray->pos_x += data->ray->plane_x * data->ray->move_speed;
	if (data->map->map[(int)(data->ray->pos_y + data->ray->plane_y
			* data->ray->move_speed)][(int)(data->ray->pos_x)] == '.')
		data->ray->pos_y += data->ray->plane_y * data->ray->move_speed;
}

void	go_left(t_parse *data)
{
	if (data->map->map[(int)(data->ray->pos_y)][(int)(data->ray->pos_x
		- data->ray->plane_x * data->ray->move_speed)] == '.')
		data->ray->pos_x -= data->ray->plane_x * data->ray->move_speed;
	if (data->map->map[(int)(data->ray->pos_y - data->ray->plane_y
			* data->ray->move_speed)][(int)(data->ray->pos_x)] == '.')
		data->ray->pos_y -= data->ray->plane_y * data->ray->move_speed;
}
