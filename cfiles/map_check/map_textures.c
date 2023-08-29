
#include "../../cub3d.h"
#include "ft_getline/ft_getline.h"

int	free_texture_lines(char **texture_path, char **direction)
{
	if (*texture_path)
		free(*texture_path);
	if (*direction)
		free(*direction);
	return (1);
}

int	save_textures_path(t_data *data, char *texture_path, char *direction)
{
	if (!data->texture->north && !ft_strcmp(direction, "NO"))
		data->texture->north = ft_strdup(texture_path);
	else if (!data->texture->south && !ft_strcmp(direction, "SO"))
		data->texture->south = ft_strdup(texture_path);
	else if (!data->texture->west && !ft_strcmp(direction, "WE"))
		data->texture->west = ft_strdup(texture_path);
	else if (!data->texture->east && !ft_strcmp(direction, "EA"))
		data->texture->east = ft_strdup(texture_path);
	else
		return (1);
	return (0);
}

int	is_possible_direction(t_data *data, t_map *file, short first_line)
{
	short	is_new_line;
	char	*direction;
	char	*texture_path;

	direction = NULL;
	texture_path = NULL;
	is_new_line = 1;
	while (is_new_line)
	{
		if (direction)
		{
			first_line = 1;
			free(direction);
		}
		direction = ft_getline(data, file->fd, &file->buffer, ' ');
		if (first_line == 0 && !direction)
			free_map_exit(data, file, "Error\nempty map\n");
		if (!direction)
			free_map_exit(data, file, "Error\ntexture faild\n");
		if (direction[0] != 0)
			is_new_line = 0;
	}
	texture_path = ft_getline(data, file->fd, &file->buffer, '\n');
	if (save_textures_path(data, texture_path, direction))
		return (free_texture_lines(&texture_path, &direction));
	free_texture_lines(&texture_path, &direction);
	return (0);
}

void	handel_textures(t_data *data, t_map *file)
{
	if (is_possible_direction(data, file, 0) || is_possible_direction(data,
			file, 1))
		free_map_exit(data, file, "Error\nfaild to read textures\n");
	if (is_possible_direction(data, file, 1) || is_possible_direction(data,
			file, 1))
		free_map_exit(data, file, "Error\nfaild to read textures\n");
	if (!data->texture->north || !data->texture->south)
		free_map_exit(data, file, "Error\nfaild to save north texture\n");
	if (!data->texture->east || !data->texture->west)
		free_map_exit(data, file, "Error\nfaild to save east texture\n");
}