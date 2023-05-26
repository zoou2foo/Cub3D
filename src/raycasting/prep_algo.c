/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:42:18 by vjean             #+#    #+#             */
/*   Updated: 2023/05/26 09:44:50 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

void	mesure_delta(t_parse *data)
{
	if (data->ray->ray_dirX == 0)
		data->ray->delta_X = 1e30;
	else
		data->ray->delta_X = fabs(1 / data->ray->ray_dirX);
	if (data->ray->ray_dirY == 0)
		data->ray->delta_Y = 1e30;
	else
		data->ray->delta_Y = fabs(1 / data->ray->ray_dirY);
}

void	prep_dda(t_parse *data)
{
	if (data->ray->ray_dirX < 0) //vers gauche
	{
		data->ray->step_x = -1;
		data->ray->sideX_dist = (data->ray->pos_X - data->ray->map_x) * data->ray->delta_X;
	}
	else
	{
		data->ray->step_x = 1; //vers droite
		data->ray->sideX_dist = (data->ray->map_x + 1.0 - data->ray->pos_X) * data->ray->delta_X;
	}
	if (data->ray->ray_dirY < 0) //en arriere
	{
		data->ray->step_y = -1;
		data->ray->sideY_dist = (data->ray->pos_Y - data->ray->map_y) * data->ray->delta_Y;
	}
	else
	{
		data->ray->step_y = 1; //en avant
		data->ray->sideY_dist = (data->ray->map_y + 1.0 - data->ray->pos_Y) * data->ray->delta_Y;
	}
}

void	get_perpendicular(t_raycast *ray) //to avoid fish eye!
{
	if (ray->side == 0)
		ray->perpendicular_wallDist = ray->sideX_dist - ray->delta_X;
	else
		ray->perpendicular_wallDist = ray->sideY_dist - ray->delta_Y;
}

void	draw_line(t_raycast *ray)
{
	//to calculate height of line to draw on screen
	ray->line_height = (int)(h / ray->perpendicular_wallDist);
	//calculate lowest and highest pixel to fill in current "stripe"
	ray->draw_start_pt = -ray->line_height / 2 + h / 2;
	if (ray->draw_start_pt < 0)
		ray->draw_start_pt = 0;
	ray->draw_end_pt = ray->line_height / 2 + h / 2;
	if (ray->draw_end_pt >= h)
		ray->draw_end_pt = h - 1;
}