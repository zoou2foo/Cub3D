/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:43:54 by vjean             #+#    #+#             */
/*   Updated: 2023/05/31 09:25:39 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	int		c;
	int		i;
	char	*ptr;

	if (!s1 || !s2)
		return (0);
	c = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = malloc(sizeof(char) * (c + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	c = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[c] != '\0')
	{
		ptr[i + c] = s2[c];
		c++;
	}
	ptr[i + c] = '\0';
	s1 = xfree(s1);
	return (ptr);
}
