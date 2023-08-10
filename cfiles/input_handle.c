
#include "../cub3d.h"

int	map_extension(char *map_path)
{
	int	i;

	i = 0;
	while (map_path[i])
		i++;
	if (i < 5)
		return (1);
	i--;
	if (map_path[i] == 'b' && map_path[i - 1] == 'u' && map_path[i - 2] == 'c'
		&& map_path[i - 3] == '.')
		return (0);
	return (1);
}

int	check_input(char *map_path)
{
	int	fd;

	if (!map_path || map_path == NULL)
		return (1);
	fd = open(map_path, O_RDONLY);
	if (fd <= 0)
	{
		ft_putstr_fd("Cant find/access map!\n", 2);
		return (1);
	}
	if (map_extension(map_path))
	{
		ft_putstr_fd("Invalid map extension!\n", 2);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	input_handle(int argc, char **argv)
{
	int		check;
	char	*map_file;

	if (argc <= 1 || argc >= 3)
	{
		ft_putstr_fd("Invalid number of parameters\n", 2);
		return (1);
	}
	map_file = ft_strj("maps/", argv[1]);
	check = check_input(map_file);
	free(map_file);
	if (check)
		return (1);
	return (0);
}
