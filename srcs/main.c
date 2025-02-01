/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:31:44 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/01 17:32:20 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_putstr("Usage: ./fdf [mapfile]\n");
        return (1);
    }

    int rows, cols;
    int **map = read_map(argv[1], &rows, &cols);
    if (!map)
    {
        ft_putstr("Error reading map file.\n");
        return (1);
    }

    // Inicializando o mlx
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");

    // Desenhando o mapa
    draw_map(map, rows, cols, mlx_ptr, win_ptr);

    mlx_loop(mlx_ptr);

    // Liberando memória
    for (int i = 0; i < rows; i++)
        free(map[i]);
    free(map);

    return (0);
}