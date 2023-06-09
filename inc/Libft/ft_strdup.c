/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:27:34 by jgagnon           #+#    #+#             */
/*   Updated: 2023/05/31 12:04:32 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	i = ft_strlen(s1) + 1;
	ptr = ft_calloc(i, sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, (char *)s1, i);
	return (ptr);
}
