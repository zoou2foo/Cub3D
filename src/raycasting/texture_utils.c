/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:26:53 by vjean             #+#    #+#             */
/*   Updated: 2023/05/26 14:18:22 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

void	transform_xpm(t_parse *data)
{
	data->xpm->EA = mlx_load_xpm42(data->ea);
	if (!data->xpm->EA)
	{
		printf("L'un des chemin des textures est invalide\n");
		exit(1);
	}
	data->xpm->WE = mlx_load_xpm42(data->we);
	if (!data->xpm->WE)
	{
		printf("L'un des chemin des textures est invalide\n");
		exit(1);
	}
	data->xpm->NO = mlx_load_xpm42(data->no);
	if (!data->xpm->NO)
	{
		printf("L'un des chemin des textures est invalide\n");
		exit(1);
	}
	data->xpm->SO = mlx_load_xpm42(data->so);
	if (!data->xpm->SO)
	{
		printf("L'un des chemin des textures est invalide\n");
		exit(1);
	}
}
