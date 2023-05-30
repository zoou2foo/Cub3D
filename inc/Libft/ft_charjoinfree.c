/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoinfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:39:30 by vjean             #+#    #+#             */
/*   Updated: 2023/05/29 14:40:06 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoinfree(const char *s1, const char c)
{
	char	*r_str;
	int		len;
	int		i;

	len = 0;
	if (s1)
		len = ft_strlen(s1);
	i = -1;
	r_str = NULL;
	if (len < 1)
	{
		r_str = malloc(sizeof(char) * 2);
		r_str[0] = c;
		r_str[1] = '\0';
	}
	else if (len > 0)
	{
		r_str = malloc(sizeof(char) * (len + 2));
		while (s1[++i] != '\0')
			r_str[i] = s1[i];
		r_str[i] = c;
		r_str[i + 1] = '\0';
	}
	xfree((char *) s1);
	return (r_str);
}
