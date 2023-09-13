#include "../includes/cub3d_bonus.h"


void draw_gun(t_data *data, int y, int x)
{
    int start_x;
    int color;
    int img_y;
    int img_x;

    start_x = x;
    img_y = 0;
    img_x = 0;
    while(img_y < data->gun->height)
    {
        x = start_x;
        img_x = 0;
        while(img_x < data->gun->width)
        {
            color = data->gun->addr[(img_y * data->gun->line_len) + img_x];
            if(color != 0xE6E6E6)
                img_pix_put(data->img, x, y, color);
            x++;
            img_x++;
        }
        y++;
        img_y++;
    }
}

void create_gun(t_data *data)
{
    /* char *path;

    path = ft_strdup("2d_imgs/knife.xpm");
    loadtextures(data, data->gun, &path); */
    open_textures(data, data->gun, "2d_imgs/LAVAROCKS.xpm");
}
