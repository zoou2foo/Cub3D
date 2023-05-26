/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:27:51 by vjean             #+#    #+#             */
/*   Updated: 2023/05/26 14:37:16 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	clear_data(t_parse *data)
{
	if (data->no != NULL)
		data->no = xfree(data->no);
	if (data->so != NULL)
		data->so = xfree(data->so);
	if (data->we != NULL)
		data->we = xfree(data->we);
	if (data->ea != NULL)
		data->ea = xfree(data->ea);
	data->floor_color = 0;
	data->ceiling_color = 0;
}
