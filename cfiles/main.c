
#include "../cub3d.h"


int	main(int argc, char **argv)
{
	t_data data;

	if (input_handle(argc, argv))
		return (1);
	if (map_check( &data.map, argv[1]))
		return (1);
	printmap(data.map);
	return (0);
}
