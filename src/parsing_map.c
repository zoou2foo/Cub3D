/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:53:34 by vjean             #+#    #+#             */
/*   Updated: 2023/05/30 15:34:46 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	middle_line(char *line, t_parse *parse)
{
	int	i;

	i = -1;
	while (line[++i] == '1' || line[i] == 32)
		;
	while (line[i] != '\0' && parse->error == good)
	{
		if (ft_charsetcmp(line[i], "NESW") == 0 && parse->map->player == 0)
			parse->map->player = line[i];
		else if (ft_charsetcmp(line[i], "NESW") == 0 && parse->map->player != 0)
		{
			parse->map->player = 'Z';
			return ;
		}
		map_space_handler(line, &i, parse);
	}
	if (parse->map->big_l < ft_strlen(line))
		parse->map->big_l = ft_strlen(line);
}

void	map_space_handler(char *line, int *i, t_parse *parse)
{
	int	k;

	k = *i;
	if (line[k] == '1' && line[k + 1] == 32)
	{
		while (line[k] != '\0' && line[++k] == 32)
			;
		if (line[k] == '1' || line[k] == '\0')
			*i = k;
	}
	else if (line[k] == '0' && line[k + 1] == 32)
	{
		while (line[k] != '\0' && line[++k] == 32)
			;
		if (line[k] == '\0')
			parse->error = map;
		*i = k;
		return ;
	}
	else
		(*i)++;
	if (line[*i] != '0' && line[*i] != '1' && line[*i] != '\0' && \
		ft_charsetcmp(line[*i], "NESW") != 0)
		parse->error = map;
}
