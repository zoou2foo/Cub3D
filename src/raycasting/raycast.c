/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:15:04 by vjean             #+#    #+#             */
/*   Updated: 2023/05/18 14:24:58 by vjean            ###   ########.fr       */
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
	data->ray->move_speed = 0.15; //need to moves
	init_player_pos(data);
	init_plane(data);
}

void	init_struct(t_parse *data)
{
	data->ray->pos_X = (int)data->map->player_x;//verifie si doit etre int ou double...
	data->ray->pos_Y = (int)data->map->player_y;
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
		data->ray->sideX_dist = (data->ray->pos_X - data->map->player_x) * data->ray->delta_X;
	}
	else
	{
		data->ray->step_x = 1; //vers droite
		data->ray->sideX_dist = (data->map->player_x + 1.0 - data->ray->pos_X) * data->ray->delta_X;
	}
	if (data->ray->ray_dirY < 0) //en arriere
	{
		data->ray->step_y = -1;
		data->ray->sideY_dist = (data->ray->pos_Y - data->map->player_y) * data->ray->delta_Y;
	}
	else
	{
		data->ray->step_y = 1; //en avant
		data->ray->sideY_dist = (data->map->player_y + 1.0 - data->ray->pos_Y) * data->ray->delta_Y;
	}
}

void	dda_algo(t_parse *data)
{
	while (1) //peut-etre mettre variable hit
	{
		if (data->ray->sideX_dist < data->ray->sideY_dist)
		{
			data->ray->sideX_dist += data->ray->delta_X;
			data->ray->pos_X += data->ray->step_x;
			data->ray->side = 0;
		}
		else
		{
			data->ray->sideY_dist += data->ray->delta_Y;
			data->ray->pos_Y += data->ray->step_y;
			data->ray->side = 1;
		}
		//hit a wall or not??
		if (data->map->map[data->ray->pos_Y][data->ray->pos_X] == '1')//or should I put > 0?? We know the wall is 1
			break ;
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

void	put_tex(t_tex *tex, mlx_image_t *image, int index, int count)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < tex->height) //comparer a quoi??
	{
		while (x < tex->width) //comparer a quoi??
		{
			mlx_put_pixel(image, index, count, tex->tab[y][x]);
			x++;
		}
		x = 0;
		y++;
	}
}

void	add_tex_wall(t_parse *data, int index)
{
	int	i;

	i = 0;
	while (i < data->ray->draw_start_pt) //plafond
	{
		mlx_put_pixel(data->image, index, i, data->CeilingColor);
		i++;
	}
	while (i < data->ray->draw_end_pt) //add texture here for walls
	{
		if (data->ray->side == 1)
		{
			if (data->ray->ray_dirY < 0) //south
				mlx_put_pixel(data->image, index, i, data->xpm->tab_so_tex->tab[i % data->xpm->tab_so_tex->height][index % data->xpm->tab_so_tex->width]); //orange
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
	while (i < h - 1) //plancher
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
	while (index < w)
	{
		init_struct(data);
		cameraX = (2 * index) / (double)w - 1;
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
	mlx_loop(data->mlx); //add keypress avant loop
	mlx_terminate(data->mlx);
}
