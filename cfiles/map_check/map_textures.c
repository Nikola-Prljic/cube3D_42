
#include "../../cub3d.h"
#include "ft_getline/ft_getline.h"

//need to replace with open xpm texture!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! <----
char *open_textures(char *texture_path)
{
	return texture_path;
}

int free_texture_lines(char **texture_path, char **direction)
{
	if(*texture_path)
		free(*texture_path);
	if(*direction)
		free(*direction);
	return 1;
}

int is_possible_direction(t_data *data, t_map *file)
{
	char *direction;
	char *texture_path;

	direction = ft_getline(file->fd, &file->buffer, ' ');
	texture_path = ft_getline(file->fd, &file->buffer, '\n');
	if(!ft_strcmp(direction, "NO"))
		data->texture->north = open_textures(texture_path);
	else if(!ft_strcmp(direction, "SO"))
		data->texture->south = open_textures(texture_path);
	else if(!ft_strcmp(direction, "WE"))
		data->texture->west = open_textures(texture_path);
	else if(!ft_strcmp(direction, "EA"))
		data->texture->east = open_textures(texture_path);
	else
		return(free_texture_lines(&texture_path, &direction));
	free_texture_lines(&texture_path, &direction);
	return (0);
}

void handel_textures(t_data *data, t_map *file)
{
	if(is_possible_direction(data, file))
		free_map_exit(data, file, "Error: faild to open textures\n");
	if(is_possible_direction(data, file))
		free_map_exit(data, file, "Error: faild to open textures\n");
	if(is_possible_direction(data, file))
		free_map_exit(data, file, "Error: faild to open textures\n");
	if(is_possible_direction(data, file))
		free_map_exit(data, file, "Error: faild to open textures\n");
	if(data->texture->north == NULL)
		free_map_exit(data, file, "Error: faild to save north texture\n");
	if(data->texture->south == NULL)
		free_map_exit(data, file, "Error: faild to save south texture\n");
	if(data->texture->east == NULL)
		free_map_exit(data, file, "Error: faild to save east texture\n");
	if(data->texture->west == NULL)
		free_map_exit(data, file, "Error: faild to save west texture\n");
}