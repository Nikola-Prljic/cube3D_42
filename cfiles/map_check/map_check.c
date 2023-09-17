/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:55:57 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/17 13:12:38 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "ft_getline/ft_getline.h"

void	malloc_data_map_first_line(t_data *data, t_map *file)
{
	data->map = malloc(sizeof(char *) * 2);
	if (!data->map)
		free_map_exit(data, file, "Error\nMalloc failed\n");
	data->map[0] = NULL;
}

char	*save_first_line(t_data *data, t_map *file, int y)
{
	char	*line;

	line = NULL;
	line = ft_getline(data, file->fd, &file->buffer, '\n');
	while (line && line[0] == 0)
	{
		free_set_null(&line);
		line = ft_getline(data, file->fd, &file->buffer, '\n');
	}
	if (isvalidchar(data, line, " 01NEWS", y) == 1)
	{
		free(line);
		free_map_exit(data, file, "Error\nWrong char in a map\n");
	}
	ft_matrix_push_back(data, file, line);
	return (line);
}

void	save_lines_loop(t_data *data, t_map *file)
{
	int		y;
	short	map_parts_after_nl;
	char	*line;

	y = 0;
	map_parts_after_nl = 0;
	line = NULL;
	malloc_data_map_first_line(data, file);
	line = save_first_line(data, file, y);
	y = 1;
	while (line)
	{
		free_set_null(&line);
		line = saveline(data, file, y, &map_parts_after_nl);
		if (line && line[0] != 0)
			y++;
	}
	data->map_y = y;
}

int	map_check(t_data *data, int fd)
{
	t_map	file;

	file.fd = fd;
	file.buffer = NULL;
	handel_textures(data, &file);
	save_lines_loop(data, &file);
	if (data->px == -1 || data->py == -1)
		free_map_exit(data, &file,
			"Error\nStart position was not found on a map\n");
	if (file.buffer)
		free(file.buffer);
	if (fd != -1)
		close(file.fd);
	surrounded_by_walls(data, data->px, data->py);
	return (0);
}
//free_data_exit(data, "ok in mapcheck.c\n", 0);
