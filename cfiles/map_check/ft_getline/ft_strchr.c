/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:17:14 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/11 16:30:16 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getline.h"

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)(&s[int_strlen(s)]));
	while (*s)
	{
		if (*s == (char)(c))
			return ((char *)(s));
		s++;
	}
	return (NULL);
}

size_t	int_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}