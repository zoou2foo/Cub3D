/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:26:53 by vjean             #+#    #+#             */
/*   Updated: 2023/05/29 08:56:55 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

void	transform_xpm(t_parse *data)
{
	data->xpm->ea = mlx_load_xpm42(data->ea);
	if (!data->xpm->ea)
	{
		printf("L'un des chemin des textures est invalide\n");
		exit(1);
	}
	data->xpm->we = mlx_load_xpm42(data->we);
	if (!data->xpm->we)
	{
		printf("L'un des chemin des textures est invalide\n");
		exit(1);
	}
	data->xpm->no = mlx_load_xpm42(data->no);
	if (!data->xpm->no)
	{
		printf("L'un des chemin des textures est invalide\n");
		exit(1);
	}
	data->xpm->so = mlx_load_xpm42(data->so);
	if (!data->xpm->so)
	{
		printf("L'un des chemin des textures est invalide\n");
		exit(1);
	}
}
