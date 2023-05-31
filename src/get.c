/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:29:56 by vjean             #+#    #+#             */
/*   Updated: 2023/05/31 12:18:00 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

char	*get_path(char *line)
{
	char	*r_get;
	char	*path;
	int		i;

	r_get = NULL;
	path = NULL;
	i = 0;
	while (line[i] != 32 && line[i] != '\0')
		i++;
	path = ft_substr(line, 0, i);
	return (path);
}

void	get_player_point(t_map *map_data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	print_double_tab(map_data->map);
	while (map_data->map[y] != NULL)
	{
		while (map_data->map[y][x] != '\0')
		{
			if (ft_charsetcmp(map_data->map[y][x], "NSEW") == 0)
			{
				map_data->player_x = x;
				map_data->player_y = y;
				return ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

static void	change_space(char *map)
{
	int	i;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == 32)
			map[i] = '1';
		i++;
	}
}

void	get_tmp_map(t_parse *data, int fd)
{
	char	*r_gnl;
	int		i;

	r_gnl = NULL;
	i = 0;
	while (data->mapbeg > 1)
	{
		r_gnl = ez_gnl(fd);
		r_gnl = xfree(r_gnl);
		data->mapbeg--;
	}
	data->map->map = malloc(sizeof(char *) * (data->map->nb_lines + 1));
	r_gnl = ez_gnl(fd);
	while (r_gnl != NULL && i <= data->map->nb_lines)
	{
		data->map->map[i] = ft_calloc(data->map->big_l + 1, sizeof(char));
		ft_strlcpy(data->map->map[i], r_gnl, ft_strlen(r_gnl) + 1);
		r_gnl = xfree(r_gnl);
		change_space(data->map->map[i]);
		r_gnl = ez_gnl(fd);
		i++;
	}
	data->map->map[i] = NULL;
	get_player_point(data->map);
}
