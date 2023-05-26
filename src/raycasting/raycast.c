/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:15:04 by vjean             #+#    #+#             */
/*   Updated: 2023/05/26 10:02:55 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

//hit a wall or not?? (2nd if)
void	dda_algo(t_parse *data)
{
	while (data->ray->hit == 0)
	{
		if (data->ray->sideX_dist < data->ray->sideY_dist)
		{
			data->ray->sideX_dist += data->ray->delta_X;
			data->ray->map_x += data->ray->step_x;
			data->ray->side = 0;
		}
		else
		{
			data->ray->sideY_dist += data->ray->delta_Y;
			data->ray->map_y += data->ray->step_y;
			data->ray->side = 1;
		}
		if (data->map->map[data->ray->map_y][data->ray->map_x] == '1')
			data->ray->hit = 1;
	}
}

void	add_tex_wall(t_parse *data, int index)
{
	long int	i;

	i = 0;
	while (i < data->ray->draw_start_pt) //ceiling
	{
		mlx_put_pixel(data->image, index, i, data->CeilingColor);
		i++;
	}
	if (data->ray->side == 1)
	{
		if (data->ray->ray_dirY < 0) //south
			prepare_teX(data, data->xpm->tab_so_tex, &index);
		else //north
			prepare_teX(data, data->xpm->tab_no_tex, &index);
	}
	else if (data->ray->side == 0)
	{
		if(data->ray->ray_dirX > 0) //east
			prepare_teX(data, data->xpm->tab_ea_tex, &index);
		else //west
			prepare_teX(data, data->xpm->tab_we_tex, &index);
	}
	if (data->ray->draw_start_pt > data->ray->draw_end_pt)
		i = h;
	else
		i = data->ray->draw_end_pt;
	while (i < h - 1) //floor
	{
		mlx_put_pixel(data->image, index, i, data->FloorColor);
		i++;
	}
}


void	go_raycast(t_parse *data)
{
	int		index;
	double	cameraX; //"les yeux" du joueur

	index = 0;
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	data->map->player_x = data->ray->pos_X; //update la pos du joueur dans la map
	data->map->player_y = data->ray->pos_Y;
	while (index < w)
	{
		init_struct(data);
		cameraX = 2 * index / (double)w - 1;
		data->ray->ray_dirX = data->ray->dir_playerX + data->ray->plane_X * cameraX;
		data->ray->ray_dirY = data->ray->dir_playerY + data->ray->plane_Y * cameraX;
		mesure_delta(data);
		prep_dda(data);
		dda_algo(data);
		get_perpendicular(data->ray);
		draw_line(data->ray);
		add_tex_wall(data, index);
		index++;
	}
}

void	start_raycast(t_parse *data)
{
	if (!(data->mlx = mlx_init(w, h, "cub3d", true)))
	{
		mlx_strerror(mlx_errno); //fonction a utiliser pour gerer les erreurs
		exit(EXIT_FAILURE); //do we need to change the error message? to make sure stuff is free?
	}
	setup_struct(data);
	go_raycast(data);
	mlx_key_hook(data->mlx, key_event, (void*)data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->image);
	mlx_terminate(data->mlx);
	exit (EXIT_SUCCESS);
}
