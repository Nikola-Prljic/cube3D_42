
#include "../../cub3d.h"
#include "ft_getline/ft_getline.h"

int is_number(char *color_rgb, int *color)
{
	if(!ft_strcmp(color_rgb, "0"))
	{
		*color = 0;
		return (0);
	}
	*color = ft_atoi(color_rgb);
	if(*color == 0)
		return (puterror("Error\nColor is not a number\n"));
	if(*color < 0)
		return (puterror("Error\nColor is smaller than 0\n"));
	if(*color > 255)
		return (puterror("Error\nColor is bigger than 255\n"));
	return(0);
}

int string_rgb_to_int(char **color_rgb, int *color)
{
	int r;
	int g;
	int b;

	if(is_number(color_rgb[0], &r))
		return (1);
	if(is_number(color_rgb[1], &g))
		return (1);
	if(is_number(color_rgb[2], &b))
		return (1);
	*color = (r << 16) + (g << 8) + b;
	return(0);
}

void get_color_code(t_data *data, t_map *file, char **color_rgb, int at_i)
{
	char c;

	c = ',';
	if(at_i == 2)
		c = '\n';
	color_rgb[at_i] = ft_getline(data, file->fd, &file->buffer, c);
	if(!color_rgb[at_i])
	{
		if(color_rgb[0])
			free(color_rgb[0]);
		if(color_rgb[1])
			free(color_rgb[1]);
		if(color_rgb[2])
			free(color_rgb[2]);
		free(color_rgb);
		free_map_exit(data, file, "Error\nColor code was not found\n");
	}
}

int save_color(t_data *data, t_map *file, char *line, char color)
{
	int color_hex;
	char **color_rgb;

	color_rgb = malloc(sizeof(char *) * 4);
	if(!color_rgb)
	{
		if(line)
			free(line);
		free_map_exit(data, file, "Error\nMalloc failed at save_color\n");
	}
	if(line[0] != color || line[1] != 0)
	{
		free_set_null(&line);
		if(color_rgb)
			free(color_rgb);
		free_map_exit(data, file, "Error\nNo color found\n");
	}
	if(line)
		free(line);
	color_rgb[0] = NULL;
	color_rgb[1] = NULL;
	color_rgb[2] = NULL;
	color_rgb[3] = NULL;
	get_color_code(data, file, color_rgb, 0);
	get_color_code(data, file, color_rgb, 1);
	get_color_code(data, file, color_rgb, 2);

	if(string_rgb_to_int(color_rgb, &color_hex))
	{
		free2d(color_rgb);
		return free_map_exit(data, file, NULL);
	}
	free2d(color_rgb);
	return(color_hex);
}

char *loop_to_not_nl( t_data *data, t_map *file )
{
	int stop_loop;
	char *line;

	line = NULL;
	stop_loop = 1;
	while(stop_loop)
	{
		if(line)
			free(line);
		line = ft_getline(data, file->fd, &file->buffer, ' ');
		if(!line)
			free_map_exit(data, file, "Error\nNo color line was found\n");
		if(line[0] != 0)
			stop_loop = 0;
	}
	return (line);
}

void handel_color_codes( t_data *data, t_map *file )
{
	char *line;

	line = NULL;
	line = loop_to_not_nl(data, file);
   	data->floor_rgb = save_color(data, file, line, 'F');
	line = loop_to_not_nl(data, file);
	data->sky_rgb = save_color(data, file, line, 'C');
}