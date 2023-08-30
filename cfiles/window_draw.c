#include "../cub3d.h"

void	img_pix_put(t_img *img, int put_x, int put_y, int color)
{
    /* char    *pixel;
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
    } */
    /* int *buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian); */

/*     for(int y = 0; y < x; ++y)
    {
        for(int x = 0; x < put_y; ++x)
        { */
            img->addr[(put_y * img->line_len) + put_x] = color;
/*         }
    } */
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
            img_pix_put(data->img, x, rect.start_y, rect.color);
            x++;
        }
        rect.start_y++;
    }
}

//need to calculate the texture in total, but draw just the what you see with img_pix_put
//calculate the size of one pixel with line 94. For resizing the texture
void draw_texure_on_walls(t_data *data, double wallStripHeight, int ray_x)
{
    double tmp;
    int y_texture;
    int y_ray_total;

    y_texture = 0;
    y_ray_total = 0;
    tmp = wallStripHeight;
    ray_x = ray_x - ray_x / 64 * 64;
    if(wallStripHeight > WINDOW_HEIGT)
        wallStripHeight = WINDOW_HEIGT;
    while(y_ray_total < tmp)
    {
        if(y_texture > TILE_SIZE)
            y_texture = 0;
        if(y_ray_total < wallStripHeight + (tmp - wallStripHeight) / 2 && y_ray_total > (tmp - wallStripHeight) / 2)
            img_pix_put(data->img, data->raycount, (double)WINDOW_HEIGT / 2.0 - tmp / 2.0 + (double)y_ray_total, data->north->addr[(y_texture * data->north->line_len) + ray_x]);
        if (y_ray_total % (int)((y_texture + 1) * (tmp  / TILE_SIZE)) == 0)
            y_texture++;
        y_ray_total++;    
    }
}

void draw_walls(t_data *data, double distance, int ray_x)
{
        double correctWallDistance;
        double distanceProjPlane;
        double wallStripHeight;
        /* ray_y--; */
    
        correctWallDistance = cos(data->rays->ray_angle - data->rays->player_dir) * distance;
        distanceProjPlane = ((double)WINDOW_HEIGT / 2.0) / 0.57735026919;
        wallStripHeight = ((double)TILE_SIZE / correctWallDistance) * distanceProjPlane;
        
        double tmp = wallStripHeight;

        if(wallStripHeight >= WINDOW_HEIGT)
            wallStripHeight = WINDOW_HEIGT;

        ray_x = ray_x - ray_x / 64 * 64;
        /* ft_rect(data, (t_rect){(double)WINDOW_HEIGT / 2.0 - wallStripHeight / 2.0, data->raycount, wallStripHeight, 1, 0xFFFFFF}); */
        int y = 0;
        int y_texture = 0;
        int x = (double)WINDOW_HEIGT / 2.0 - tmp / 2.0;
        double scale = (tmp  / TILE_SIZE);
        double top = wallStripHeight + (tmp - wallStripHeight) / 2;
        double bottom = (tmp - wallStripHeight) / 2;
        while(y < tmp)
        {
            if(y <= top && y > bottom)
                img_pix_put(data->img, data->raycount, x + y, data->north->addr[(y_texture * data->north->line_len) + ray_x]);
            if (y % (int)((y_texture + 1) * scale) == 0)
                y_texture++;
            y++;    
        }
}

/* void create_img_addr(t_data *data)
{
    data->north->addr = (int *)mlx_get_data_addr(data->north->img, &data->north->bpp, &data->north->line_len, &data->north->endian);
    if(!data->north->addr)
        printf("faild\n");
    data->north->line_len /= 4;
} */

void draw_minimap(t_data *data/* , int start_y, int start_x */)
{
    int y;
    int x;
    int mini_map_tidle; 

    y = 0;
    mini_map_tidle = TILE_SIZE * MAP_SIZE;
    ft_rect(data, (t_rect){(data->rays->py - 3) * MAP_SIZE, (data->rays->px - 3) * MAP_SIZE, 15 * MAP_SIZE, 15 * MAP_SIZE, 0xFF0000});
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