/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:26:19 by vjean             #+#    #+#             */
/*   Updated: 2023/05/26 14:35:55 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

t_parse	*init_check(void)
{
	t_parse	*data;

	data = malloc(sizeof(t_parse));
	data->no = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->we = NULL;
	data->floor_color = 0;
	data->ceiling_color = 0;
	data->treat_floor = false;
	data->treat_ceiling = false;
	data->error = GOOD;
	data->mapbeg = 0;
	data->map = malloc(sizeof(t_map));
	data->map->player = 0;
	data->map->first_line = false;
	data->map->last_line = false;
	data->map->map = NULL;
	data->map->player_x = 0;
	data->map->player_y = 0;
	data->map->direction = 0;
	data->map->nb_lines = 0;
	return (data);
}
