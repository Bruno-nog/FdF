/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:09:28 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/07 19:55:31 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int update_zoom(void *param)
{
    t_data *data = (t_data *)param;
    int redraw = 0;

    // Zoom contínuo enquanto a tecla estiver pressionada
    if (data->zoom_in)
    {
        data->zoom *= 1.02;  // Taxa mais suave
        redraw = 1;
    }
    if (data->zoom_out)
    {
        data->zoom *= 0.98;  // Taxa mais suave
        redraw = 1;
    }

    if (redraw)
    {
        data->zoom = fmaxf(data->zoom, 0.1);
        data->zoom = fminf(data->zoom, 50.0);
        
        int min_x, min_y, max_x, max_y;
        calculate_projected_bounds(data, &min_x, &min_y, &max_x, &max_y, data->zoom);
        
        data->offset_x = (WIN_WIDTH - (max_x - min_x)) / 2 - min_x;
        data->offset_y = (WIN_HEIGHT - (max_y - min_y)) / 2 - min_y;
        
        draw_map(data);
    }
    return 0;
}

int handle_key_press(int keycode, void *param)
{
    t_data *data = (t_data *)param;
    
    if (keycode == 65307) // ESC
        handle_close(data);
    if (keycode == 65361) // seta esquerda
        data->offset_x -= 10;
    if (keycode == 65363) // seta direita
        data->offset_x += 10;
    if (keycode == 65362) // seta cima
        data->offset_y -= 10;
    if (keycode == 65364) // seta baixo
        data->offset_y += 10;
    if (keycode == 61 || keycode == 65451) // "+"
        data->zoom_in = 1;  // Mantém pressionado
    if (keycode == 45 || keycode == 65453) // "-"
        data->zoom_out = 1;  // Mantém pressionado
    
    draw_map(data);
    return 0;
}

int handle_key_release(int keycode, void *param)
{
    t_data *data = (t_data *)param;
    
    // Libera apenas quando a tecla específica for solta
    if (keycode == 61 || keycode == 65451)
        data->zoom_in = 0;
    else if (keycode == 45 || keycode == 65453)
        data->zoom_out = 0;
    
    return 0;
}
