/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:54:50 by vjean             #+#    #+#             */
/*   Updated: 2023/05/26 14:53:20 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	first_parse(int fd, t_parse *data)
{
	char		*line;
	char		read_ret[2];
	static int	nb_line;
	int			r_read;

	line = NULL;
	r_read = read(fd, &read_ret, 1);
	while (r_read > 0 && read_ret[0] != '\n')
	{
		if (line == NULL)
			line = ft_strdup(read_ret);
		else
			line = ft_strjoin_free(line, read_ret);
		r_read = read(fd, &read_ret, 1);
	}
	nb_line++;
	if ((data->map->first_line == true && data->map->last_line == true) \
		&& (read_ret[0] == '\n' || line != NULL))
		data->error = CUB_FILE;
	if (line != NULL && data->error == GOOD)
		parse_line(line, data);
	line = xfree(line);
	if (data->map->first_line == true && data->mapbeg == 0)
		data->mapbeg = nb_line;
	return (r_read);
}

unsigned int	ft_uatoi(const char *str, t_parse *data)
{
	unsigned int	nb;
	int				i;

	nb = 0;
	i = 0;
	while (str[i] >= 0x09 && (str[i] <= 0x0d || str[i] == 0x20))
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] == '-' || str[i] == '+' || \
			ft_isalpha(str[i]) == 1)
		{
			data->error = COLOR;
			return (0);
		}
		nb = (nb * 10) + (str[i] - 0x30);
		i++;
	}
	if (nb > 255)
		data->error = COLOR;
	return (nb);
}

void	print_double_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("%s", tab[i]);
		i++;
	}
	printf("\n");
}

char	*ez_gnl(int fd)
{
	char	*line;
	char	read_ret[2];

	line = NULL;
	read_ret[1] = '\0';
	while (read(fd, &read_ret, 1) > 0)
	{
		if (line == NULL)
			line = ft_strdup(read_ret);
		else
			line = ft_strjoin_free(line, read_ret);
		if (read_ret[0] == '\n')
			break ;
	}
	return (line);
}

void	flood_fill(t_parse *data, int y, int x)
{
	int	i;

	i = 0;
	while (data->map->map[i])
		i++;
	if ((y - 1 < 0 || x - 1 < 0 || y + 1 >= i \
			|| x + 1 >= ft_strlen(data->map->map[y]))
		&& ft_strchr("0", data->map->map[y][x]))
	{
		data->error = MAP;
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
