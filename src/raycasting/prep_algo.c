/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:42:18 by vjean             #+#    #+#             */
/*   Updated: 2023/05/29 08:08:18 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

/*		FOUR FUNCTIONS		*/

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
	if (data->ray->ray_dirX < 0)
	{
		data->ray->step_x = -1;
		data->ray->sideX_dist = (data->ray->pos_X - data->ray->map_x)
			* data->ray->delta_X;
	}
	else
	{
		data->ray->step_x = 1;
		data->ray->sideX_dist = (data->ray->map_x + 1.0 - data->ray->pos_X)
			* data->ray->delta_X;
	}
	if (data->ray->ray_dirY < 0)
	{
		data->ray->step_y = -1;
		data->ray->sideY_dist = (data->ray->pos_Y - data->ray->map_y)
			* data->ray->delta_Y;
	}
	else
	{
		data->ray->step_y = 1;
		data->ray->sideY_dist = (data->ray->map_y + 1.0 - data->ray->pos_Y)
			* data->ray->delta_Y;
	}
}

//to avoid fish eye!
void	get_perpendicular(t_raycast *ray)
{
	if (ray->side == 0)
		ray->perpendicular_wallDist = ray->sideX_dist - ray->delta_X;
	else
		ray->perpendicular_wallDist = ray->sideY_dist - ray->delta_Y;
}

//to calculate height of line to draw on screen (first line)
//calculate lowest and highest pixel to fill in current "stripe" (2nd line)
void	draw_line(t_raycast *ray)
{
	ray->line_height = (int)(H / ray->perpendicular_wallDist);
	ray->draw_start_pt = -ray->line_height / 2 + H / 2;
	if (ray->draw_start_pt < 0)
		ray->draw_start_pt = 0;
	ray->draw_end_pt = ray->line_height / 2 + H / 2;
	if (ray->draw_end_pt >= H)
		ray->draw_end_pt = H - 1;
}
