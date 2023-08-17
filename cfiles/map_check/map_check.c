
#include "../../cub3d.h"
#include "ft_getline/ft_getline.h"

void	malloc_data_map_first_line(t_data *data, t_map *file)
{
	data->map = malloc(sizeof(char*) * 2);
	if(!data->map)
		free_map_exit(data, file, "Error\nmalloc faild\n");
	data->map[0] = NULL;
}

void	save_lines_loop(t_data *data, t_map *file)
{
	int 	y;
	char	*line;

	y = 0;
	line = NULL;
	malloc_data_map_first_line(data, file);
	line = saveline(data, file, y);
	y = 1;
	while(line)
	{
		free(line);
		line = saveline(data, file, y);
		y++;
	}
	data->map_y = y - 1;
}

int	map_check(t_data *data, int fd)
{
	t_map	file;

	file.fd = fd;
	file.buffer = NULL;
	handel_textures(data, &file);
	save_lines_loop(data, &file);

	/* printmap(data->map);  *////////delte

	if(data->px == -1 || data->py == -1)
		free_map_exit(data, &file, "Error\nstart position was not found on map\n");
	if(file.buffer)
		free(file.buffer);
	if(fd != -1)
		close(file.fd);
	
	surrounded_by_walls(data, data->px, data->py);

	printmap(data->map); ///////delte

	/* printf("ok in mapcheck.c\n");
	free_map_exit(data, &file, NULL); */

	return (0);
}
