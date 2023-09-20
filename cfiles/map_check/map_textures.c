/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:02:12 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/20 11:18:00 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "ft_getline/ft_getline.h"

int	free_texture_lines(t_handle_textures *data_line)
{
	if (data_line->texture_path)
		free(data_line->texture_path);
	if (data_line->direction)
		free(data_line->direction);
	return (1);
}

int	save_textures_path(t_data *data, t_map *file, char *texture_path,
		char *direction)
{
	if (!data->texture->north && !ft_strcmp(direction, "NO"))
		data->texture->north = ft_strdup(texture_path);
	else if (!data->texture->south && !ft_strcmp(direction, "SO"))
		data->texture->south = ft_strdup(texture_path);
	else if (!data->texture->west && !ft_strcmp(direction, "WE"))
		data->texture->west = ft_strdup(texture_path);
	else if (!data->texture->east && !ft_strcmp(direction, "EA"))
		data->texture->east = ft_strdup(texture_path);
	else if (data->floor_rgb == -1 && !ft_strcmp(direction, "F"))
		data->floor_rgb = save_color(data, file, texture_path);
	else if (data->sky_rgb == -1 && !ft_strcmp(direction, "C"))
		data->sky_rgb = save_color(data, file, texture_path);
	else
		return (1);
	return (0);
}

void	getline_test_it(t_data *data, t_map *file, t_handle_textures *data_line,
		int first_line)
{
	data_line->direction = ft_getline(data, file->fd, &file->buffer, ' ');
	if (first_line == 0 && !data_line->direction)
		free_map_exit(data, file, "Error\nEmpty map\n");
	if (!data_line->direction)
		free_map_exit(data, file, "Error\nTexture failed\n");
	if (data_line->direction[0] != 0)
		data_line->is_new_line = 0;
}

int	rm_space_in_front(t_handle_textures *d)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (!d->texture_path[0] || d->texture_path[0] != ' ')
		return (0);
	while (d->texture_path[i] == ' ')
		i++;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(d->texture_path) - i
			+ 1));
	if (!new_str)
		return (1);
	while (d->texture_path[i])
	{
		new_str[j] = d->texture_path[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free(d->texture_path);
	d->texture_path = new_str;
	return (0);
}

int	is_possible_direction(t_data *data, t_map *file, short first_line)
{
	t_handle_textures	data_line;

	data_line.direction = NULL;
	data_line.texture_path = NULL;
	data_line.is_new_line = 1;
	while (data_line.is_new_line)
	{
		if (data_line.direction)
		{
			first_line = 1;
			free(data_line.direction);
		}
		getline_test_it(data, file, &data_line, first_line);
	}
	data_line.texture_path = ft_getline(data, file->fd, &file->buffer, '\n');
	rm_space_in_front(&data_line);
	data->data_line = &data_line;
	if (save_textures_path(data, file, data_line.texture_path,
			data_line.direction))
		return (free_texture_lines(&data_line));
	free_texture_lines(&data_line);
	return (0);
}

void	handel_textures(t_data *data, t_map *file)
{
	if (is_possible_direction(data, file, 0) || is_possible_direction(data,
			file, 1))
		free_map_exit(data, file, "Error\nfailed to read textures\n");
	if (is_possible_direction(data, file, 1) || is_possible_direction(data,
			file, 1))
		free_map_exit(data, file, "Error\nfailed to read textures\n");
	if (is_possible_direction(data, file, 1) || is_possible_direction(data,
			file, 1))
		free_map_exit(data, file, "Error\nfaild to read colors\n");
	if (!data->texture->north || !data->texture->south)
		free_map_exit(data, file,
			"Error\nfailed to save north/south texture\n");
	if (!data->texture->east || !data->texture->west)
		free_map_exit(data, file, "Error\nfailed to save east/west texture\n");
	if (data->floor_rgb == -1 || data->sky_rgb == -1)
		free_map_exit(data, file, "Error\nfailed to save floor/sky color\n");
}
