/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:05:32 by vjean             #+#    #+#             */
/*   Updated: 2023/05/26 14:54:39 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

void	rotate_cam(struct mlx_key_data key, t_parse *data)
{
	double	oldDirX;
	double	oldPlaneX;
	double	speed;

	oldDirX = data->ray->dir_playerX;
	oldPlaneX = data->ray->plane_X;
	speed = 0.06;
	if (key.key == 263)
	{
		//printf("ON TOURNE À GAUCH'!\n");
		data->ray->dir_playerX = data->ray->dir_playerX * cos(-speed) - data->ray->dir_playerY * sin(-speed);
		data->ray->dir_playerY = oldDirX * sin(-speed) + data->ray->dir_playerY * cos(-speed);
		data->ray->plane_X = data->ray->plane_X * cos(-speed) - data->ray->plane_Y * sin(-speed);
		data->ray->plane_Y = oldPlaneX * sin(-speed) + data->ray->plane_Y * cos(-speed);
	}
	else if (key.key == 262)
	{
		//printf("ON TOURNE À DROUAITE!\n");
		data->ray->dir_playerX = data->ray->dir_playerX * cos(speed) - data->ray->dir_playerY * sin(speed);
		data->ray->dir_playerY = oldDirX * sin(speed) + data->ray->dir_playerY * cos(speed);
		data->ray->plane_X = data->ray->plane_X * cos(speed) - data->ray->plane_Y * sin(speed);
		data->ray->plane_Y = oldPlaneX * sin(speed) + data->ray->plane_Y * cos(speed);
	}
	go_raycast(data);
}

void	lets_move(struct mlx_key_data key, t_parse *data)
{
	if (key.key == 87)
		go_ahead(data);
	else if (key.key == 65)
		go_left(data);
	else if (key.key == 83)
		go_back(data);
	else if (key.key == 68)
		go_right(data);
	go_raycast(data);
}

void	key_event(struct mlx_key_data key, void *data)
{
	t_parse	*tmp;

	tmp = data;
	if (key.key == 263 || key.key == 262)
		rotate_cam(key, tmp);
	if (key.key == 87 || key.key == 83 || key.key == 65 || key.key == 68)
		lets_move(key, tmp);
	else if (key.key == 256)
	{
		mlx_close_window(tmp->mlx);
		mlx_terminate(tmp->mlx);
		printf("exit cub3d\n");
		exit (1);
	}
}