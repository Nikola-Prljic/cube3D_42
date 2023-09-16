/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:17:14 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/16 19:10:26 by nprljic          ###   ########.fr       */
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

void	map_size_check_and_read_protaction(t_data *data, char *buf,
		char *remain, int ret)
{
	if (ret == -1)
	{
		free_set_null(&buf);
		free_set_null(&remain);
		free_data_exit(data, "Error\nRead failed at ft_putline\n", 1);
	}
	data->read_size += ret;
	if (data->read_size > sizeof(char) * 10000)
	{
		free_set_null(&buf);
		free_set_null(&remain);
		free_data_exit(data, "Error\nMap is bigger than 10000 * sizeof(char)\n",
			1);
	}
}
