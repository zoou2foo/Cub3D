/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:05:32 by vjean             #+#    #+#             */
/*   Updated: 2023/05/29 09:02:47 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

void	do_rotate(struct mlx_key_data key, t_parse *data, double olddirx,
double oldplanex)
{
	double	speed;

	speed = 0.06;
	if (key.key == 263)
	{
		data->ray->dir_playerx = data->ray->dir_playerx * cos(-speed) \
		- data->ray->dir_playery * sin(-speed);
		data->ray->dir_playery = olddirx * sin(-speed) \
		+ data->ray->dir_playery * cos(-speed);
		data->ray->plane_x = data->ray->plane_x * cos(-speed) \
		- data->ray->plane_y * sin(-speed);
		data->ray->plane_y = oldplanex * sin(-speed) + data->ray->plane_y \
		* cos(-speed);
	}
	else if (key.key == 262)
	{
		data->ray->dir_playerx = data->ray->dir_playerx * cos(speed) \
		- data->ray->dir_playery * sin(speed);
		data->ray->dir_playery = olddirx * sin(speed) + data->ray->dir_playery \
		* cos(speed);
		data->ray->plane_x = data->ray->plane_x * cos(speed) \
		- data->ray->plane_y * sin(speed);
		data->ray->plane_y = oldplanex * sin(speed) + data->ray->plane_y \
		* cos(speed);
	}
}

void	rotate_cam(struct mlx_key_data key, t_parse *data)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->ray->dir_playerx;
	oldplanex = data->ray->plane_x;
	do_rotate(key, data, olddirx, oldplanex);
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
