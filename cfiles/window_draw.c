#include "../cub3d.h"

void	img_pix_put(t_mlx_img *img, int x, int y, int color)
{
    char    *pixel;
    int		i;

    i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    while (i >= 0)
    {
        if (img->endian != 0)
            *pixel++ = (color >> i) & 0xFF;
        else
            *pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
        i -= 8;
    }
}

void ft_rect(t_data *data, t_rect rect)
{
    int x;
    int end_y;
    int end_x;

    if(rect.start_x < 0 || rect.start_x > WINDOW_WITH || rect.start_y < 0 || rect.size_y > WINDOW_HEIGT)
        return ;
    if(rect.size_x < 0 || rect.start_x + rect.size_x > WINDOW_WITH || rect.size_y < 0 || rect.start_y + rect.size_y > WINDOW_HEIGT)
        return ;
    x = rect.start_x;
    end_y = rect.start_y + rect.size_y;
    end_x = rect.start_x + rect.size_x;
    while(rect.start_y < end_y)
    {
        x = rect.start_x;
        while(x < end_x)
        {
            img_pix_put(&data->img, x, rect.start_y, rect.color);
            x++;
        }
        rect.start_y++;
    }
}

void draw_walls(t_data *data, double distance)
{
        double correctWallDistance;
        double distanceProjPlane;
        double wallStripHeight;
    
        correctWallDistance = cos(data->rays->ray_angle - data->rays->player_dir) * distance;
        distanceProjPlane = ((double)WINDOW_HEIGT / 2.0) / 0.57735026919;
        wallStripHeight = ((double)TILE_SIZE / correctWallDistance) * distanceProjPlane;
        if(wallStripHeight >= WINDOW_HEIGT)
            wallStripHeight = WINDOW_HEIGT;
        ft_rect(data, (t_rect){(double)WINDOW_HEIGT / 2.0 - wallStripHeight / 2.0, data->raycount, wallStripHeight, 1, 0xFFFFFF});
}

void put_texture_x(t_data *data, t_xpm_img *img, int y_pos, int y_color, int zoom)
{
    int x_color = 0, x_pos = 0, tmp = zoom;

    while(x_color < img->width)
    {
        /* while(zoom > 0)
        {

        } */
        while(zoom > 0)
        {
            img_pix_put(&data->img, x_pos + 100, y_pos + 100, img->addr[(y_color * img->line_len) + x_color]);
            x_pos++;
            zoom--;
        }
        /* img_pix_put(&data->img, x_pos + 100, y_pos + 100, img->addr[(y_color * img->line_len) + x_color]);
        x_pos++; */
        x_color++;
        zoom = tmp;
    }
}

void draw_texture(t_data *data)
{
    int y = 0, x = 0, y_pos = 0, x_pos = 0, zoom_faktor = data->zoom_faktor, tmp = zoom_faktor;

    data->north->addr = (int *)mlx_get_data_addr(data->north->img, &data->north->bpp, &data->north->line_len, &data->north->endian);
    if(!data->north->addr)
        printf("faild\n");
    data->north->line_len /= 4;
    while(y < data->north->height)
    {
        x = 0;
        x_pos = 0;
        while(zoom_faktor > 0)
        {
            put_texture_x(data, data->north, y_pos, y, tmp);
            y_pos++;
            zoom_faktor--;
        }
        /* put_texture_x(data, data->north, y_pos, y, zoom_faktor);
        y_pos++; */
        zoom_faktor = tmp;
        y++;
    }
}

/* void draw_minimap(t_data *data)
{
    int y;
    int x;

    y = 0;
    int mini_map_tidle = TILE_SIZE * MAP_SIZE;
    ft_rect(data, (t_rect){data->rays->py * MAP_SIZE - 3, data->rays->px * MAP_SIZE - 3, 6, 6, 0xFF0000});
    while(data->map[y])
    {
        x = 0;
        while(data->map[x])
        {
            if(data->map[y][x] == '1')
                ft_rect(data, (t_rect){y * mini_map_tidle, x * mini_map_tidle, mini_map_tidle, mini_map_tidle, 0x555555});
            x++;
        }
        y++;
    }
} */

/* void minimap(t_data *data)
{
    int mini_map_tidle = TILE_SIZE * MAP_SIZE;
    ft_rect(data, (t_rect){data->rays->py * MAP_SIZE - 3, data->rays->px * MAP_SIZE - 3, 6, 6, 0xFF0000});
    draw_minimap(data, data->rays->py * MAP_SIZE - 8, data->rays->px * MAP_SIZE - 8);
} */

void draw_minimap(t_data *data/* , int start_y, int start_x */)
{
    int y;
    int x;
    int mini_map_tidle; 

    y = 0;
    mini_map_tidle = TILE_SIZE * MAP_SIZE;
    ft_rect(data, (t_rect){data->rays->py * MAP_SIZE - 3, data->rays->px * MAP_SIZE - 3, 6, 6, 0xFF0000});
    while(data->map[y])
    {
        x = 0;
        while(data->map[y][x])
        {
            if(data->map[y][x] == '1')
                ft_rect(data, (t_rect){y * mini_map_tidle, x * mini_map_tidle, mini_map_tidle, mini_map_tidle, 0x555555});
            x++;
        }
        y++;
    }
}