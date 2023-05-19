/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:05:32 by vjean             #+#    #+#             */
/*   Updated: 2023/05/19 10:58:51 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

void	rotate_cam(struct mlx_key_data key, t_raycast *ray)
{
	double	oldDirX;
	double	oldPlaneX;
	double	speed;

	oldDirX = ray->dir_playerX;
	oldPlaneX = ray->plane_X;
	speed = 0.06;
	if (key.key == 263)
	{
		//printf("ON TOURNE À GAUCH'!\n");
		ray->dir_playerX = ray->dir_playerX * cos(-speed) - ray->dir_playerY * sin(-speed);
		ray->dir_playerY = oldDirX * sin(-speed) + ray->dir_playerY * cos(-speed);
		ray->plane_X = ray->plane_X * cos(-speed) - ray->plane_Y * sin(-speed);
		ray->plane_Y = oldPlaneX * sin(-speed) + ray->plane_Y * cos(-speed);
	}
	else if (key.key == 262)
	{
		//printf("ON TOURNE À DROUAITE!\n");
		ray->dir_playerX = ray->dir_playerX * cos(speed) - ray->dir_playerY * sin(speed);
		ray->dir_playerY = oldDirX * sin(speed) + ray->dir_playerY * cos(speed);
		ray->plane_X = ray->plane_X * cos(speed) - ray->plane_Y * sin(speed);
		ray->plane_Y = oldPlaneX * sin(speed) + ray->plane_Y * cos(speed);
	}
}

void	lets_move(struct mlx_key_data key, t_parse *data)
{
	if (key.key == 87)// W; MLX_PRESS && MLX_REPEAT: pour action...
		go_ahead(data);
	else if (key.key == 65) // A
	 	go_left(data);
	else if (key.key == 83) // S
		go_back(data);
	else if (key.key == 68) // D
	 	go_right(data);

}

void key_event(struct mlx_key_data key, void *data)
{
	t_parse *tmp;

	tmp = data;
	//printf("Key pressed : %d\n", key.key);
	if (key.key == 263 || key.key == 262)
		rotate_cam(key, tmp->ray);
	if (key.key == 87 || key.key == 83 || key.key == 65 || key.key == 68)
		lets_move(key, tmp);
	else if (key.key == 256) //ESC
	{
		mlx_close_window(tmp->mlx);
		mlx_terminate(tmp->mlx);
		printf("exit cub3d\n");
		//free_stuff(data);
		exit (1);
	}
//	tmp->image->pixels = ft_memset((void*)tmp->image->pixels, 0, ((h * w) * sizeof(int)));
	go_raycast(tmp);
}