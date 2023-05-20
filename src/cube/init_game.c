/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:22:58 by vjean             #+#    #+#             */
/*   Updated: 2023/05/20 09:34:25 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

void	start_mlx(t_parse *data)
{
	int					y;
	int					x;

	y = 0;
	x = 0;
	if (!(data->mlx = mlx_init(1920, 1080, "cub3d", true)))
	{
		mlx_strerror(mlx_errno); //fonction a utiliser pour gerer les erreurs
		ft_free_tab((void*)data->map->map);
		ft_free_null(data);
		exit(EXIT_FAILURE);
	}
	if(!(data->image = mlx_new_image(data->mlx, 64, 64))) //size of map??
	{
		mlx_close_window(data->mlx);//ferme la fenetre
		ft_free_tab((void*)data->map->map);
		ft_free_null(data);
		exit(EXIT_FAILURE);
	}
	while (y <= 63) //à modifier ⬇️
	{
		while (x <= 63)
		{
			if ((x % 2) == 0)
				mlx_put_pixel(data->image, x, y, 0xff0000ff);
			else if ((x % 2) == 1)
				mlx_put_pixel(data->image, x, y, 0x0000ffff);
			x++;
		}
		x = 0;
		y++;
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		mlx_delete_image(data->mlx, data->image);
		mlx_close_window(data->mlx);
		exit(EXIT_FAILURE);
	}
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}