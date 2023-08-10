#include "../../cub3d.h"

int map_open( char *map_name, int *fd )
{
	char	*path;

	path = ft_strj( "maps/", map_name );
	*fd = open( path, O_RDONLY );
    if(path)
	    free(path);
	if(*fd == -1)
        return (puterror("Error: map open faild\n"));
	return (0);
}

int map_read( int fd, char **mapstr )
{
	int		ret;
	char	*buf;

	buf = malloc((100 + 1) * sizeof(char));
	if (!buf)
    {
        close(fd);
        return (puterror("Error: malloc faild\n"));
    }
	ret = 1;
	while (ret != 0)
	{
		ret = read(fd, buf, 100);
		if (ret == -1)
		{
            close(fd);
			free(buf);
			if(*mapstr)
				free(*mapstr);
			return (puterror("Error: read faild\n"));
		}
		buf[ret] = '\0';
		*mapstr = ft_linejoin(*mapstr, buf);
	}
	free(buf);
    close(fd);
	return (0);
}