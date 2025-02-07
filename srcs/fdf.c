/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:19:50 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/07 19:54:40 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void draw_line(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr)
{
    int dx, dy, sx, sy, err, e2;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = (x1 < x2) ? 1 : -1;
    sy = (y1 < y2) ? 1 : -1;
    err = dx - dy;

    while (1)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 0xFFFFFF);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}
void draw_map(t_data *data)
{
    int x, y;
    int x1, y1, x2, y2;
    int world_x, world_y, world_x2, world_y2;
    void *img;
    char *addr;
    int bpp, line_length, endian;

    // Cria uma imagem off-screen (buffer)
    img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    addr = mlx_get_data_addr(img, &bpp, &line_length, &endian);

    for (y = 0; y < data->rows; y++)
    {
        for (x = 0; x < data->cols; x++)
        {
            /* 
             * Calcula as coordenadas "mundiais" para o ponto atual 
             * (sem offset).
             */
            world_x = x * 20 * data->zoom;
            world_y = y * 20 * data->zoom - data->map[y][x] * 2 * data->zoom;

            /* Aplica a projeção isométrica */
            projection_iso(&world_x, &world_y, data->map[y][x]);

            /* Soma os offsets para obter a posição final na tela */
            x1 = world_x + data->offset_x;
            y1 = world_y + data->offset_y;

            /* Conecta com o ponto à direita, se houver */
            if (x < data->cols - 1)
            {
                world_x2 = (x + 1) * 20 * data->zoom;
                world_y2 = y * 20 * data->zoom - data->map[y][x + 1] * 2 * data->zoom;
                projection_iso(&world_x2, &world_y2, data->map[y][x + 1]);
                x2 = world_x2 + data->offset_x;
                y2 = world_y2 + data->offset_y;
                draw_line_img(x1, y1, x2, y2, addr, line_length, bpp, 0);
            }
            /* Conecta com o ponto abaixo, se houver */
            if (y < data->rows - 1)
            {
                world_x2 = x * 20 * data->zoom;
                world_y2 = (y + 1) * 20 * data->zoom - data->map[y + 1][x] * 2 * data->zoom;
                projection_iso(&world_x2, &world_y2, data->map[y + 1][x]);
                x2 = world_x2 + data->offset_x;
                y2 = world_y2 + data->offset_y;
                draw_line_img(x1, y1, x2, y2, addr, line_length, bpp, 0);
            }
        }
    }

    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, 0, 0);
    mlx_destroy_image(data->mlx_ptr, img);
}

void calculate_projected_bounds(t_data *data, int *min_x, int *min_y, int *max_x, int *max_y, float zoom)
{
    *min_x = INT_MAX;
    *min_y = INT_MAX;
    *max_x = INT_MIN;
    *max_y = INT_MIN;

    for (int y = 0; y < data->rows; y++)
    {
        for (int x = 0; x < data->cols; x++)
        {
            int wx = x * 20 * zoom;
            int wy = y * 20 * zoom - data->map[y][x] * 2 * zoom;
            projection_iso(&wx, &wy, data->map[y][x]);
            
            if (wx < *min_x) *min_x = wx;
            if (wx > *max_x) *max_x = wx;
            if (wy < *min_y) *min_y = wy;
            if (wy > *max_y) *max_y = wy;
        }
    }
}