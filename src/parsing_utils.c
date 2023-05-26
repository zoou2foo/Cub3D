#include "../inc/Cub3D.h"

int	extract_color(t_parse *data, char *line, int nb_bits, int j)
{
	char			*hex;
	unsigned int	id_color;
	int				k;

	k = 0;
	id_color = 0;
	hex = NULL;
	while (line[k] != '\0' && ft_isdigit(line[k]) == 1)
		k++;
	if (ft_isalpha(line[k]) == 1 || k == 0)
		return (-1);
	hex = ft_substr(line, 0, k);
	id_color = ft_uatoi(hex, data);
	id_color = id_color << nb_bits;
	if (data->error == GOOD && j == 4)
		data->floor_color |= id_color;
	else if (data->error == GOOD && j == 5)
		data->ceiling_color |= id_color;
	hex = xfree(hex);
	if (nb_bits == 8 && j == 4)
		data->treat_floor = true;
	else if (nb_bits == 8 && j == 5)
		data->treat_ceiling = true;
	return(k);
}	