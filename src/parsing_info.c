/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:25:05 by vjean             #+#    #+#             */
/*   Updated: 2023/05/31 12:20:22 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	parse_line(char *line, t_parse *map_check)
{
	int				i;
	int				j;

	i = -1;
	j = 0;
	while (line[++i] == 32)
		;
	if (map_check->map->first_line == false && ft_isdigit(line[i]))
		map_check->map->first_line = true;
	if (map_check->map->first_line == true)
	{
		if (map_check->error == good)
			middle_line(line, map_check);
		map_check->map->nb_lines++;
		return ;
	}
	while ((ft_strncmp(&line[i], g_side_tab[j], 3)) != 0 && j < 4)
		j++;
	if (j < 4)
		parse_path(map_check, &line[i], j);
	while (j < 6 && ft_strncmp(&line[i], g_side_tab[j], 2) != 0)
		j++;
	if (j < 6 && j >= 4)
		parse_color(map_check, &line[i], j);
}

void	parse_color(t_parse *data, char *line, int j)
{
	int	i;
	int	nb_bits;
	int	k;

	i = 1;
	nb_bits = 24;
	k = 0;
	while (line[i] != '\0' && nb_bits > 0)
	{
		while (line[i] != '\0' && line[i] == 32)
			i++;
		k = extract_color(data, &line[i], nb_bits, j);
		if (k == -1)
			break ;
		nb_bits -= 8;
		i += k;
		while (line[i] != '\0' && line[i] == 32)
			i++;
		if (line[i] != '\0' && line[i++] != ',' && nb_bits > 0)
			break ;
	}
	if (nb_bits > 0)
		data->error = color;
}

int	parse_name(char *map)
{
	int	i;

	i = 0;
	while (map[i] != '\0' && map[i] != '.')
		i++;
	if (map[i] == '.')
	{
		if (ft_strncmp(&map[i], ".cub", 5) == 0)
			return (0);
		else
		{
			while (map[i] != '\0' && map[i] != '/')
				i++;
			return (parse_name(&map[i]));
		}
	}
	return (-1);
}

t_parse	*parse_info(char *map)
{
	t_parse	*mapcheck;
	int		fd;

	fd = 0;
	if (parse_name(map) != 0)
		return (NULL);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (NULL);
	mapcheck = init_check();
	while ((first_parse(fd, mapcheck)) > 0 && mapcheck->error == good)
		;
	close(fd);
	check_parse_info(mapcheck);
	if (mapcheck->error == good)
		fd = open(map, O_RDONLY);
	get_tmp_map(mapcheck, fd);
	flood_fill(mapcheck, mapcheck->map->player_y, mapcheck->map->player_x);
	if (mapcheck->error != good)
		error_handler(mapcheck);
	return (mapcheck);
}

void	parse_path(t_parse *map_check, char *line, int j)
{
	int	i;

	i = 0;
	while (line[i] == 32)
		i++;
	i += 2;
	while (line[++i] == 32)
		;
	if (j == 0 && map_check->no == NULL)
		map_check->no = get_path(&line[i]);
	else if (j == 1 && map_check->so == NULL)
		map_check->so = get_path(&line[i]);
	else if (j == 2 && map_check->we == NULL)
		map_check->we = get_path(&line[i]);
	else if (j == 3 && map_check->ea == NULL)
	map_check->ea = get_path(&line[i]);
}
