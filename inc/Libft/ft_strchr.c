/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:09:25 by jgagnon           #+#    #+#             */
/*   Updated: 2023/06/01 10:56:02 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

// {
// 	int	i;

// 	i = -1;
// 	while (str[++i] != '\0' && str[i] != (char) c)
// 		;
// 	if (str[i] != '\0')
// 		return ((char *)&str[i]);
// 	else
// 		return (0);
// }
char	*ft_strchr(const char *s, int c)

{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
