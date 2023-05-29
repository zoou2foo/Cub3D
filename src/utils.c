/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:54:50 by vjean             #+#    #+#             */
/*   Updated: 2023/05/26 14:53:20 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

unsigned int	ft_uatoi(const char *str, t_parse *data)
{
	unsigned int	nb;
	int				i;

	nb = 0;
	i = 0;
	while (str[i] >= 0x09 && (str[i] <= 0x0d || str[i] == 0x20))
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] == '-' || str[i] == '+' || \
			ft_isalpha(str[i]) == 1)
		{
			data->error = color;
			return (0);
		}
		nb = (nb * 10) + (str[i] - 0x30);
		i++;
	}
	if (nb > 255)
		data->error = color;
	return (nb);
}

void	print_double_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("\n");
}

char	*ez_gnl(int fd)
{
	char	*line;
	char	read_ret[2];

	line = NULL;
	read_ret[1] = '\0';
	while (read(fd, &read_ret, 1) > 0)
	{
		if (read_ret[0] == '\n')
			break ;
		if (line == NULL)
			line = ft_strdup(read_ret);
		else
			line = ft_strjoin_free(line, read_ret);
	}
	return (line);
}
