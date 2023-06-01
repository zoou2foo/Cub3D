/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:37:06 by vjean             #+#    #+#             */
/*   Updated: 2023/05/30 14:18:57 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	main(int argc, char **argv)
{
	t_parse	*data;

	if (argc != 2)
	{
		printf("Veuillez fournir un fichier au format .cub\n");
		return (-1);
	}
	data = parse_info(argv[1]);
	if (data == NULL)
	{
		printf("Le fichier ne peut être ouvert ou a une erreur de format\n");
		return (-1);
	}
	add_texture(data);
	if (data->error == good)
	{
		start_raycast(data);
		free_everything(data);
	}
	return (0);
}
