/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:01:54 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/18 16:53:36 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "ft_getline/ft_getline.h"

int	charinstr(char c, char *valid_chars)
{
	int	i;

	i = 0;
	if (!valid_chars || c == 0)
		return (1);
	while (valid_chars[i])
	{
		if (c == valid_chars[i])
			return (0);
		i++;
	}
	return (1);
}

int	isvalidchar(t_data *data, char *mapstr, char *valid_chars, int y)
{
	int	x;

	x = 0;
	if (!mapstr)
		return (0);
	while (mapstr[x])
	{
		if (mapstr[x] == 'N' || mapstr[x] == 'E' || mapstr[x] == 'W'
			|| mapstr[x] == 'S')
		{
			if (data->px != -1)
				return (1);
			data->px = x;
			data->py = y;
		}
		if (charinstr(mapstr[x], valid_chars))
			return (1);
		x++;
	}
	if (data->map_x < x)
		data->map_x = x;
	return (0);
}

char	*saveline(t_data *data, t_map *file, int y, short *map_parts_after_nl)
{
	char	*line;

	line = NULL;
	line = ft_getline(data, file->fd, &file->buffer, '\n');
	if (line && line[0] == 0)
	{
		*map_parts_after_nl = 1;
		return (line);
	}
	if (line && (isvalidchar(data, line, " 01NEWS", y) == 1))
	{
		free(line);
		free_map_exit(data, file, "Error\nWrong char in a map\n");
	}
	if (line && *map_parts_after_nl)
	{
		free(line);
		free_map_exit(data, file, "Error\nMap seperated by a new line\n");
	}
	ft_matrix_push_back(data, file, line);
	return (line);
}
