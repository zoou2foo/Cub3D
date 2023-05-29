/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:42:18 by vjean             #+#    #+#             */
/*   Updated: 2023/05/29 09:01:11 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

/*		FOUR FUNCTIONS		*/

void	mesure_delta(t_parse *data)
{
	if (data->ray->ray_dirx == 0)
		data->ray->delta_x = 1e30;
	else
		data->ray->delta_x = fabs(1 / data->ray->ray_dirx);
	if (data->ray->ray_diry == 0)
		data->ray->delta_y = 1e30;
	else
		data->ray->delta_y = fabs(1 / data->ray->ray_diry);
}

void	prep_dda(t_parse *data)
{
	if (data->ray->ray_dirx < 0)
	{
		data->ray->step_x = -1;
		data->ray->sidex_dist = (data->ray->pos_x - data->ray->map_x)
			* data->ray->delta_x;
	}
	else
	{
		data->ray->step_x = 1;
		data->ray->sidex_dist = (data->ray->map_x + 1.0 - data->ray->pos_x)
			* data->ray->delta_x;
	}
	if (data->ray->ray_diry < 0)
	{
		data->ray->step_y = -1;
		data->ray->sidey_dist = (data->ray->pos_y - data->ray->map_y)
			* data->ray->delta_y;
	}
	else
	{
		data->ray->step_y = 1;
		data->ray->sidey_dist = (data->ray->map_y + 1.0 - data->ray->pos_y)
			* data->ray->delta_y;
	}
}

//to avoid fish eye!
void	get_perpendicular(t_raycast *ray)
{
	if (ray->side == 0)
		ray->perpendicular_walldist = ray->sidex_dist - ray->delta_x;
	else
		ray->perpendicular_walldist = ray->sidey_dist - ray->delta_y;
}

//to calculate height of line to draw on screen (first line)
//calculate lowest and highest pixel to fill in current "stripe" (2nd line)
void	draw_line(t_raycast *ray)
{
	ray->line_height = (int)(H / ray->perpendicular_walldist);
	ray->draw_start_pt = -ray->line_height / 2 + H / 2;
	if (ray->draw_start_pt < 0)
		ray->draw_start_pt = 0;
	ray->draw_end_pt = ray->line_height / 2 + H / 2;
	if (ray->draw_end_pt >= H)
		ray->draw_end_pt = H - 1;
}
