/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:03:55 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/12 19:09:46 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_number(char *color_rgb, int *color)
{
	if (!ft_strcmp(color_rgb, "0"))
	{
		*color = 0;
		return (0);
	}
	*color = ft_atoi(color_rgb);
	if (*color == 0)
		return (puterror("Error\nColor is not a number\n"));
	if (*color < 0)
		return (puterror("Error\nColor is smaller than 0\n"));
	if (*color > 255)
		return (puterror("Error\nColor is bigger than 255\n"));
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	tmp = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!tmp)
		return (NULL);
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	free_data_exit(t_data *data, char *msg)
{
	free_data(data);
	if (msg)
		puterror(msg);
	exit(1);
}

void	free_set_null(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
