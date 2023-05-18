/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:21:07 by vjean             #+#    #+#             */
/*   Updated: 2023/05/18 14:42:44 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

void	go_ahead(t_parse *data)
{
	if (data->map->map[data->map->player_x][(int)(data->map->player_x + data->ray->plane_X * data->ray->move_speed)] == '0')
		data->map->player_x += data->ray->plane_X * data->ray->move_speed;
	if (data->map->map[data->map->player_y][(int)(data->map->player_y + data->ray->plane_X * data->ray->move_speed)] == '0')
		data->map->player_y += data->ray->plane_Y * data->ray->move_speed;

}