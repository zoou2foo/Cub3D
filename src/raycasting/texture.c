/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 08:47:20 by vjean             #+#    #+#             */
/*   Updated: 2023/05/18 17:18:26 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

int	create_colour(int red, int green, int blue, int trans)
{
	return (red << 24 | green << 16 | blue << 8 | trans);
}

//to put in static or not
t_tex	*create_array_pxl(xpm_t *wall)
{
	t_tex		*texture;
	int	x;
	int	y;
	int			count;

	y = -1;
	count = 0;
	texture = ft_calloc(1, sizeof(t_tex));
	texture->tab = ft_calloc(sizeof(int*), wall->texture.height + 1);
	while (++y < (int)wall->texture.height)
	{
		x = -1;
		texture->tab[y] = ft_calloc(sizeof(int), (wall->texture.width));
		while (++x < (int)wall->texture.width)
		{
			texture->tab[y][x] = create_colour(wall->texture.pixels[count + 0], \
			wall->texture.pixels[count + 1], wall->texture.pixels[count + 2], \
			wall->texture.pixels[count + 3]);
			count += 4;
		}
	}
	texture->width = wall->texture.width;
	texture->height = wall->texture.height;
	return (texture);
}

void	add_texture(t_parse *data)
{
	//xpm mettre en local
	
	data->xpm = malloc(sizeof(t_xpm));
	data->xpm->EA = mlx_load_xpm42(data->EA);
	if (!data->xpm->EA)
		exit(1);//need to better deal error and free stuff
	data->xpm->WE = mlx_load_xpm42(data->WE);
	if (!data->xpm->WE)
		exit(1);//need to better deal error and free stuff
	data->xpm->NO = mlx_load_xpm42(data->NO);
	if (!data->xpm->NO)
		exit(1);//need to better deal error and free stuff
	data->xpm->SO = mlx_load_xpm42(data->SO);
	if (!data->xpm->SO)
		exit(1);//need to better deal error and free stuff
	data->xpm->tab_ea_tex = create_array_pxl(data->xpm->EA);
	data->xpm->tab_we_tex = create_array_pxl(data->xpm->WE);
	data->xpm->tab_so_tex = create_array_pxl(data->xpm->SO);
	data->xpm->tab_no_tex = create_array_pxl(data->xpm->NO);

}
