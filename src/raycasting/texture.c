/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 08:47:20 by vjean             #+#    #+#             */
/*   Updated: 2023/05/29 08:07:57 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cub3D.h"

/*	FIVE FUNCTIONS	*/

int	create_colour(int red, int green, int blue, int trans)
{
	return (red << 24 | green << 16 | blue << 8 | trans);
}

//to put in static or not
t_tex	*create_array_pxl(xpm_t *wall)
{
	t_tex	*texture;
	int		x;
	int		y;
	int		count;

	y = -1;
	count = 0;
	texture = ft_calloc(1, sizeof(t_tex));
	texture->tab = ft_calloc(sizeof(int *), wall->texture.height + 1);
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
	data->xpm = malloc(sizeof(t_xpm));
	transform_xpm(data);
	data->xpm->tab_ea_tex = create_array_pxl(data->xpm->EA);
	data->xpm->tab_we_tex = create_array_pxl(data->xpm->WE);
	data->xpm->tab_so_tex = create_array_pxl(data->xpm->SO);
	data->xpm->tab_no_tex = create_array_pxl(data->xpm->NO);
}

void	put_texture(t_parse *data, t_tex *text, int *i)
{
	double	dist;
	double	pos;
	int		tex_y;
	int		j;

	dist = 1.0 * text->height / data->ray->line_height;
	pos = ((double) data->ray->draw_start_pt - (double) H / 2
			+ (double) data->ray->line_height / 2) * dist;
	if (pos < 0)
		pos = 0;
	j = data->ray->draw_start_pt - 1;
	while (++j < data->ray->draw_end_pt)
	{
		tex_y = (int) pos;
		if (pos > text->height - 1)
			pos = text->height - 1;
		pos += dist;
		mlx_put_pixel(data->image, *i, j, text->tab[tex_y][data->ray->tex_x]);
	}
}

void	prepare_tex(t_parse *data, t_tex *text, int *i)
{
	double	hit;

	hit = 0;
	if (data->ray->side == 0)
		hit = data->ray->pos_Y + data->ray->perpendicular_wallDist
			* data->ray->ray_dirY;
	else if (data->ray->side == 1)
		hit = data->ray->pos_X + data->ray->perpendicular_wallDist
			* data->ray->ray_dirX;
	hit -= (int) hit;
	data->ray->tex_x = (int)(hit * (double) text->width);
	if (data->ray->side == 0 && data->ray->ray_dirX > 0)
		data->ray->tex_x = text->width - data->ray->tex_x - 1;
	if (data->ray->side == 1 && data->ray->ray_dirY < 0)
		data->ray->tex_x = text->width - data->ray->tex_x - 1;
	put_texture(data, text, i);
}
