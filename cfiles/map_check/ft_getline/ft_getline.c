/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:00:58 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/11 19:34:02 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getline.h"

// #1 creates a new malloc string just for the first time
char	*ft_new_str(t_data *data, int fd, char *remain, char delimiter)
{
	int		ret;
	char	*buf;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
	{
		free_set_null(&remain);
		free_data_exit(data, "Error\nMalloc failed at ft_putline");
	}
	ret = 1;
	while (!ft_strchr(remain, delimiter) && !ft_strchr(remain, '\n')
		&& ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free_set_null(&buf);
			free_set_null(&remain);
			free_data_exit(data, "Error\nRead failed at ft_putline");
		}
		buf[ret] = '\0';
		remain = ft_linejoin(data, remain, buf);
	}
	free(buf);
	return (remain);
}

// #2 prints the line
char	*ft_putline(t_data *data, char *remain, char delimiter)
{
	char	*line;
	int		i;

	if (!*remain)
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != delimiter && remain[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
	{
		free_set_null(&remain);
		free_data_exit(data, "Error\nMalloc failed at ft_putline");
	}
	i = 0;
	while (remain[i] && remain[i] != delimiter && remain[i] != '\n')
	{
		line[i] = remain[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	free_remain_data_exit(t_data *data, char **remain, char **line)
{
	free_set_null(line);
	free_set_null(remain);
	free_data_exit(data, "Error\nMalloc failed at ft_putline");
}

// #3 malloc a new without the printed string. frees the old one.
char	*ft_next_str(t_data *data, char *remain, char delimiter, char *line)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	while (remain[i] && remain[i] != delimiter && remain[i] != '\n')
		i++;
	if (!remain[i])
	{
		free(remain);
		return (NULL);
	}
	str = (char *)malloc((int_strlen(remain) - i + 1) * sizeof(char));
	if (!str)
		free_remain_data_exit(data, &remain, &line);
	x = 0;
	while (remain[++i])
		str[x++] = remain[i];
	str[x] = '\0';
	free(remain);
	return (str);
}

//buffer is for freeing if something remains
char	*ft_getline(t_data *data, int fd, char **remain, char delimiter)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	*remain = ft_new_str(data, fd, *remain, delimiter);
	if (!remain)
		return (NULL);
	line = ft_putline(data, *remain, delimiter);
	*remain = ft_next_str(data, *remain, delimiter, line);
	return (line);
}

/* int main()
{
    int fd;
    int x = 0;
    char *str;
	char *buffer = NULL;

    fd = open("test.txt", O_RDONLY);
    while(x++ < 2)
	{
        printf("line %i = %s\n", x, str = ft_getline(fd, &buffer, 't'));
		free(str);
		printf("line %i = %s", x, str = get_next_line(fd, &buffer, 'c'));
		free(str);
	}
    printf("buffer = %s", buffer);
	if(buffer)
		free(buffer);
    close(fd);
    return(0);
} */
