/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:25:43 by jgagnon           #+#    #+#             */
/*   Updated: 2023/05/30 15:23:03 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	extract_color(t_parse *data, char *line, int nb_bits, int j)
{
	char			*hex;
	unsigned int	id_color;
	int				k;

	k = 0;
	id_color = 0;
	hex = NULL;
	while (line[k] != '\0' && ft_isdigit(line[k]) == 1)
		k++;
	if (ft_isalpha(line[k]) == 1 || k == 0)
		return (-1);
	hex = ft_substr(line, 0, k);
	id_color = ft_uatoi(hex, data);
	id_color = id_color << nb_bits;
	if (data->error == good && j == 4)
		data->floor_color |= id_color;
	else if (data->error == good && j == 5)
		data->ceiling_color |= id_color;
	hex = xfree(hex);
	if (nb_bits == 8 && j == 4)
		data->treat_floor = true;
	else if (nb_bits == 8 && j == 5)
		data->treat_ceiling = true;
	return (k);
}

void	flood_fill(t_parse *data, int y, int x)
{
	int	i;

	i = 0;
	while (data->map->map[i])
		i++;
	if ((y - 1 < 0 || x - 1 < 0 || y + 1 >= i \
			|| x + 1 >= ft_strlen(data->map->map[y]))
		&& (ft_strchr("0 ", data->map->map[y][x]) != 0))
	{
		data->error = map;
		error_handler(data);
	}
	if (data->map->map[y][x] == '0'
		|| ft_charsetcmp(data->map->map[y][x], "NSEW") == 0)
		data->map->map[y][x] = '.';
	else
		return ;
	flood_fill(data, y, x - 1);
	flood_fill(data, y + 1, x);
	flood_fill(data, y, x + 1);
	flood_fill(data, y - 1, x);
	flood_fill(data, y + 1, x + 1);
	flood_fill(data, y + 1, x - 1);
	flood_fill(data, y - 1, x + 1);
	flood_fill(data, y - 1, x - 1);
}

static char	*read_concatenate(char *r_read, char *line)
{
	if (line == NULL)
		line = ft_strdup(r_read);
	else if (line != NULL)
		line = ft_strjoin_free(line, r_read);
	return (line);
}

int	first_parse(int fd, t_parse *data)
{
	char		*line;
	char		read_ret[2];
	static int	nb_line;
	int			r_read;

	line = NULL;
	 ft_bzero(read_ret, 2);
	r_read = read(fd, &read_ret, 1);
	while (r_read > 0 && read_ret[0] != '\n')
	{
		line = read_concatenate(read_ret, line);
		r_read = read(fd, &read_ret, 1);
	}
	if (r_read == -1)
		data->error = cub_file;
	nb_line++;
	if ((data->map->first_line == true && data->map->last_line == true) \
		&& (read_ret[0] == '\n' || line != NULL))
		data->error = cub_file;
	if (line != NULL && data->error == good)
		parse_line(line, data);
	line = xfree(line);
	if (data->map->first_line == true && data->mapbeg == 0)
		data->mapbeg = nb_line;
	return (r_read);
}
