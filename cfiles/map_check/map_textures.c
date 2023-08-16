
#include "../../cub3d.h"
#include "ft_getline/ft_getline.h"

int free_texture_lines(char **texture_path, char **direction)
{
	if(*texture_path)
		free(*texture_path);
	if(*direction)
		free(*direction);
	return 1;
}

int save_textures_path(t_data *data, char *texture_path, char *direction)
{
	if(!data->texture->north && !ft_strcmp(direction, "NO"))
		data->texture->north = ft_strdup(texture_path);
	else if(!data->texture->south && !ft_strcmp(direction, "SO"))
		data->texture->south = ft_strdup(texture_path);
	else if(!data->texture->west && !ft_strcmp(direction, "WE"))
		data->texture->west = ft_strdup(texture_path);
	else if(!data->texture->east && !ft_strcmp(direction, "EA"))
		data->texture->east = ft_strdup(texture_path);
	else
		return(1);
	return(0);
}

int is_possible_direction(t_data *data, t_map *file)
{
	char *direction;
	char *texture_path;

	direction = ft_getline(file->fd, &file->buffer, ' ');
	texture_path = ft_getline(file->fd, &file->buffer, '\n');
	if(save_textures_path(data, texture_path, direction))
		return(free_texture_lines(&texture_path, &direction));
	free_texture_lines(&texture_path, &direction);
	return (0);
}

int is_possible_first_direction(t_data *data, t_map *file)
{
	char *direction;
	char *texture_path;

	direction = ft_getline(file->fd, &file->buffer, ' ');
	texture_path = ft_getline(file->fd, &file->buffer, '\n');
	if(!direction)
		free_map_exit(data, file, "Error\nempty map\n");
	if(save_textures_path(data, texture_path, direction))
		return(free_texture_lines(&texture_path, &direction));
	free_texture_lines(&texture_path, &direction);
	return (0);
}

void handel_textures(t_data *data, t_map *file)
{
	if(is_possible_first_direction(data, file))
		free_map_exit(data, file, "Error\nfaild to open textures\n");
	if(is_possible_direction(data, file))
		free_map_exit(data, file, "Error\nfaild to open textures\n");
	if(is_possible_direction(data, file))
		free_map_exit(data, file, "Error\nfaild to open textures\n");
	if(is_possible_direction(data, file))
		free_map_exit(data, file, "Error\nfaild to open textures\n");
	if(data->texture->north == NULL)
		free_map_exit(data, file, "Error\nfaild to save north texture\n");
	if(data->texture->south == NULL)
		free_map_exit(data, file, "Error\nfaild to save south texture\n");
	if(data->texture->east == NULL)
		free_map_exit(data, file, "Error\nfaild to save east texture\n");
	if(data->texture->west == NULL)
		free_map_exit(data, file, "Error\nfaild to save west texture\n");
}