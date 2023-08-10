
#include "../cub3d.h"

void init_data( t_data *data )
{
	data->map = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
}

void free_data(t_data *data)
{
	if(data->map)
		free2d(data->map);
}

int	main(int argc, char **argv)
{
	t_data data;

	init_data( &data );
	if (input_handle(argc, argv))
		return (1);
	if (map_check( &data.map, argv[1]) || window_loop( &data ))
	{
		free_data(&data);
		return (1);
	}
	free_data(&data);
	return (0);
}
