/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:08:06 by vjean             #+#    #+#             */
/*   Updated: 2023/05/29 08:47:40 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

/**
 * Function to free a pointer
 * @param ptr to free
 */
void	ft_free_null(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

/**
 * Function to free a double pointer array
 * @param tab in void so it can take any type of variable
 */
void	ft_free_tab(void **tab)
{
	int	i;

	if (tab)
	{
		i = -1;
		while (tab[++i])
			ft_free_null(tab[i]);
		ft_free_null(tab);
	}
}

void	free_tex_paths(t_parse *data)
{
	if (data->ea)
		ft_free_null(data->ea);
	if (data->we)
		ft_free_null(data->we);
	if (data->no)
		ft_free_null(data->no);
	if (data->so)
		ft_free_null(data->so);
}

void	free_ptr_xpm(t_xpm *xpm)
{
	if (xpm->ea)
		ft_free_null(xpm->ea);
	if (xpm->we)
		ft_free_null(xpm->we);
	if (xpm->no)
		ft_free_null(xpm->no);
	if (xpm->so)
		ft_free_null(xpm->so);
	if (xpm->tab_ea_tex)
		ft_free_null(xpm->tab_ea_tex);
	if (xpm->tab_no_tex)
		ft_free_null(xpm->tab_no_tex);
	if (xpm->tab_so_tex)
		ft_free_null(xpm->tab_so_tex);
	if (xpm->tab_we_tex)
		ft_free_null(xpm->tab_we_tex);
}

void	free_everything(t_parse *data)
{
	free_tex_paths(data);
	ft_free_tab((void *)data->map->map);
	free_ptr_xpm(data->xpm);
	ft_free_null(data->map);
	ft_free_null(data->xpm);
	ft_free_null(data->ray);
	free(data);
}
