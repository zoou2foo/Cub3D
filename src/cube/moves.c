/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:21:07 by vjean             #+#    #+#             */
/*   Updated: 2023/05/19 13:03:54 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

void	go_ahead(t_parse *data)
{
	if (data->map->map[(int)data->ray->pos_Y][(int)(data->ray->pos_X + data->ray->dir_playerX * data->ray->move_speed)] == '.')
		data->ray->pos_X += data->ray->dir_playerX * data->ray->move_speed;
	if (data->map->map[(int)(data->ray->pos_Y + data->ray->dir_playerY * data->ray->move_speed)][(int)data->ray->pos_X] == '.')
		data->ray->pos_Y += data->ray->dir_playerY * data->ray->move_speed;
}

void	go_back(t_parse *data)
{
	if (data->map->map[(int)data->ray->pos_Y][(int)(data->ray->pos_X - data->ray->dir_playerX * data->ray->move_speed)] == '.')
		data->ray->pos_X -= data->ray->dir_playerX * data->ray->move_speed;
	if (data->map->map[(int)(data->ray->pos_Y - data->ray->dir_playerY * data->ray->move_speed)][(int)data->ray->pos_X] == '.')
		data->ray->pos_Y -= data->ray->dir_playerY * data->ray->move_speed;
}

// gauche et droite
void	go_right(t_parse *data)
{
	if (data->map->map[(int)data->ray->pos_Y][(int)(data->ray->pos_X + data->ray->plane_X * data->ray->move_speed)] == '.')
		data->ray->pos_X += data->ray->plane_X * data->ray->move_speed;
	if (data->map->map[(int)data->ray->pos_Y][(int)(data->ray->pos_X + data->ray->plane_X * data->ray->move_speed)] == '.')
		data->ray->pos_Y += data->ray->plane_Y * data->ray->move_speed;
}

void	go_left(t_parse *data)
{
	if (data->map->map[(int)data->ray->pos_Y][(int)(data->ray->pos_X + data->ray->plane_X * data->ray->move_speed)] == '.')
		data->ray->pos_X -= data->ray->plane_X * data->ray->move_speed;
	if (data->map->map[(int)data->ray->pos_Y][(int)(data->ray->pos_X + data->ray->plane_X * data->ray->move_speed)] == '.')
		data->ray->pos_Y -= data->ray->plane_Y * data->ray->move_speed;
}