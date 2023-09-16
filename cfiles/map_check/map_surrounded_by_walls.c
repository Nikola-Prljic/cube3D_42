/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_surrounded_by_walls.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:04:01 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/16 14:07:56 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	floodfill(t_data *data, t_path pos, char fill, char fill_with)
{
	if (pos.y < 0 || pos.x < 0)
		return ;
	if (!data->map_copy[pos.y] || pos.x > ft_strlen(data->map_copy[pos.y])
		|| data->map_copy[pos.y][pos.x] == 0)
		free_data_exit(data, "Error\nMap is not surrounded by 1\n", 1);
	if (pos.y < 0 || pos.x < 0 || charinstr(data->map_copy[pos.y][pos.x],
		"01F"))
		free_data_exit(data, "Error\nMap is not surrounded by 1\n", 1);
	if (pos.y < 0 || pos.x < 0 || data->map_copy[pos.y][pos.x] != fill)
		return ;
	data->map_copy[pos.y][pos.x] = fill_with;
	floodfill(data, (t_path){pos.x + 1, pos.y}, fill, fill_with);
	floodfill(data, (t_path){pos.x + 1, pos.y + 1}, fill, fill_with);
	floodfill(data, (t_path){pos.x - 1, pos.y}, fill, fill_with);
	floodfill(data, (t_path){pos.x - 1, pos.y - 1}, fill, fill_with);
	floodfill(data, (t_path){pos.x, pos.y + 1}, fill, fill_with);
	floodfill(data, (t_path){pos.x - 1, pos.y + 1}, fill, fill_with);
	floodfill(data, (t_path){pos.x, pos.y - 1}, fill, fill_with);
	floodfill(data, (t_path){pos.x + 1, pos.y - 1}, fill, fill_with);
}

int	look_for_zero_save_pos(t_data *data, t_path *pos)
{
	int	y;
	int	x;

	y = 0;
	while (data->map_copy[y])
	{
		x = 0;
		while (data->map_copy[y][x])
		{
			if (data->map_copy[y][x] == '0')
			{
				pos->y = y;
				pos->x = x;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

char	**deep_copy_matrix(t_data *data)
{
	int		y;
	int		i;
	char	**new_matrix;

	y = 0;
	new_matrix = malloc(sizeof(char *) * (data->map_y + 1));
	if (!new_matrix)
		free_data_exit(data, "Error:\nMalloc failed in deep_copy_matrix\n", 1);
	while (data->map[y])
	{
		new_matrix[y] = ft_strdup(data->map[y]);
		if (!new_matrix[y])
		{
			i = -1;
			while (++i < y)
				free(new_matrix[i]);
			free(new_matrix);
			free_data_exit(data, "Error:\nMalloc failed in deep_copy_matrix\n",
				1);
		}
		y++;
	}
	new_matrix[y] = NULL;
	return (new_matrix);
}

int	surrounded_by_walls(t_data *data, int x, int y)
{
	t_path	pos;

	pos.x = x;
	pos.y = y;
	data->map_copy = deep_copy_matrix(data);
	data->map_copy[y][x] = '0';
	floodfill(data, pos, '0', 'F');
	while (look_for_zero_save_pos(data, &pos))
		floodfill(data, pos, '0', 'F');
	map_check_walls(data);
	if (data->map_copy)
		free2d(data->map_copy);
	data->map_copy = NULL;
	return (0);
}
