/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:15:04 by vjean             #+#    #+#             */
/*   Updated: 2023/05/22 10:25:43 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

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

void init_plane(t_parse *data)
{
	data->ray->plane_X = data->ray->dir_playerY * -0.66;
	if (data->ray->dir_playerX != 0)
		data->ray->plane_Y = data->ray->dir_playerX * 0.66;
	else
		data->ray->plane_Y = 0.0;
}

void	setup_struct(t_parse *data)
{
	data->ray = malloc(sizeof(t_raycast));
	data->image = mlx_new_image(data->mlx, w, h);
	data->ray->pos_X = data->map->player_x + 0.5;
	data->ray->pos_Y = data->map->player_y + 0.5;
	data->ray->map_x = (int)data->ray->pos_X;
	data->ray->map_y = (int)data->ray->pos_Y;
	data->ray->move_speed = 0.15;
	init_player_pos(data);
	init_plane(data);
}

void	init_struct(t_parse *data)
{
	data->ray->hit = 0;
	data->ray->map_x = (int)data->ray->pos_X;//verifie si doit etre int ou double...
	data->ray->map_y = (int)data->ray->pos_Y;
}

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

void	dda_algo(t_parse *data)
{
	while (data->ray->hit == 0) //peut-etre mettre variable hit
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
		//hit a wall or not??
		if (data->map->map[data->ray->map_y][data->ray->map_x] == '1')//or should I put > 0?? We know the wall is 1
			data->ray->hit = 1;
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
	int	line_height;
	//to calculate height of line to draw on screen
	line_height = (int)(h / ray->perpendicular_wallDist);
	//calculate lowest and highest pixel to fill in current "stripe"
	ray->draw_start_pt = -line_height / 2 + h / 2;
	if (ray->draw_start_pt < 0)
		ray->draw_start_pt = 0;
	ray->draw_end_pt = line_height / 2 + h / 2;
	if (ray->draw_end_pt >= h)
		ray->draw_end_pt = h - 1;
}


//need 2 ratios. 1st: Where you are in the wall -> where are you in the image? (texture)
// 2nd ratio: ratio mur:image (so it can fit. How much do you have to reduce the image?). Starting from the top
// Then, with ratios, then we print (mlx_put_pixel).

void	add_tex_wall(t_parse *data, int index)
{
	int		i;
	double	ratio_hit_img;
	double	ratio_img_to_wall;

	i = 0;
	ratio_hit_img =
	ratio_img_to_wall =
	while (i < data->ray->draw_start_pt) //ceiling
	{
		mlx_put_pixel(data->image, index, i, data->CeilingColor);
		i++;
	}
	while (i < data->ray->draw_end_pt) //add texture here for walls
	{
		if (data->ray->side == 1)
		{
			if (data->ray->ray_dirY < 0) //south
				mlx_put_pixel(data->image, index, i, data->xpm->tab_so_tex->tab[i % (data->xpm->tab_so_tex->height)][index % (data->xpm->tab_so_tex->width)]); //orange
			else //north
				mlx_put_pixel(data->image, index, i, data->xpm->tab_no_tex->tab[i % data->xpm->tab_no_tex->height][index % data->xpm->tab_no_tex->width]); //red
		}
		else if (data->ray->side == 0)
		{
			if(data->ray->ray_dirX > 0) //east
				mlx_put_pixel(data->image, index, i, data->xpm->tab_ea_tex->tab[i % data->xpm->tab_ea_tex->height][index % data->xpm->tab_ea_tex->width]); //pink;
			else //west
				mlx_put_pixel(data->image, index, i, data->xpm->tab_we_tex->tab[i % data->xpm->tab_we_tex->height][index % data->xpm->tab_we_tex->width]); //yellow
		}
		i++;
	}
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
		//function to look if side 1, 2, 3 to then, select the correct array of int
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
