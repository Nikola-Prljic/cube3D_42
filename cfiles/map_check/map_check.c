
#include "../../cub3d.h"
#include "ft_getline/ft_getline.h"

void malloc_data_map_first_line(t_data *data, t_map *file)
{
	data->map = malloc(sizeof(char*) * 2);
	if(!data->map)
		free_map_exit(data, file, "Error\nmap_open faild\n");
	data->map[0] = NULL;
}

int map_check(t_data *data, int fd)
{
	int y;
	char	*line;
	t_map	file;

	y = 0;
	line = NULL;
	file.fd = fd;
	file.buffer = NULL;
	handel_textures(data, &file);
	malloc_data_map_first_line(data, &file);
	line = saveline(data, &file, y);
	y = 1;
	while(line)
	{
		free(line);
		line = saveline(data, &file, y);
		y++;
	}
	data->map_y = y - 1;

	printmap(data->map);

	if(data->px == -1 || data->py == -1)
		free_map_exit(data, &file, "Error\nStart position was not found on map\n");
	if(file.buffer)
		free(file.buffer);
	if(fd != -1)
		close(file.fd);
	ft_fillmap(data, data->px, data->py);

	printmap(data->map);
	/* free_map_exit(data, &file, NULL); */

	return (0);
}
