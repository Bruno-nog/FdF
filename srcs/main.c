/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:31:44 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/07 19:55:07 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int main(int argc, char **argv)
{
    t_data  data;

    if (argc != 2)
    {
        write(1, "Usage: ./fdf [mapfile]\n", 23);
        return (1);
    }
    data.map = read_map(argv[1], &data.rows, &data.cols);
    if (!data.map)
    {
        write(1, "Error reading map file.\n", 24);
        return (1);
    }
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");

    // Inicialização simplificada
    // Na seção de inicialização
    data.zoom = 1.0;
    data.zoom_in = 0;
    data.zoom_out = 0;
    data.offset_x = 0;  // Use offset_x diretamente
    data.offset_y = 0;  // Em vez de pan_offset
    
    // 1. Calcular limites iniciais com zoom 1.0
    int min_x, min_y, max_x, max_y;
    calculate_projected_bounds(&data, &min_x, &min_y, &max_x, &max_y, data.zoom);
    
    // 2. Ajustar zoom automaticamente para caber na janela
    float width_ratio = (WIN_WIDTH - 40) / (float)(max_x - min_x);
    float height_ratio = (WIN_HEIGHT - 40) / (float)(max_y - min_y);
    data.zoom = fminf(width_ratio, height_ratio);
    data.zoom = fmaxf(data.zoom, 0.1);  // Limite mínimo de zoom

    // 3. Recalcular limites com novo zoom
    calculate_projected_bounds(&data, &min_x, &min_y, &max_x, &max_y, data.zoom);
    
    // 4. Centralizar o mapa
    data.offset_x = (WIN_WIDTH - (max_x - min_x)) / 2 - min_x;
    data.offset_y = (WIN_HEIGHT - (max_y - min_y)) / 2 - min_y;

    draw_map(&data);

    // Restante mantido igual
    mlx_hook(data.win_ptr, 2, 1L << 0, handle_key_press, &data);
    mlx_hook(data.win_ptr, 3, 1L << 1, handle_key_release, &data);
    mlx_hook(data.win_ptr, 17, 0, handle_close, &data);
    mlx_loop_hook(data.mlx_ptr, update_zoom, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}
