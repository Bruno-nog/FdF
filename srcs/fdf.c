/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:19:50 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/01 17:32:05 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void draw_line(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr)
{
    mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 0xFFFFFF);
    mlx_pixel_put(mlx_ptr, win_ptr, x2, y2, 0xFFFFFF);
}

void draw_map(int **map, int rows, int cols, void *mlx_ptr, void *win_ptr)
{
    int x, y;

    for (y = 0; y < rows; y++)
    {
        for (x = 0; x < cols; x++)
        {
            if (x < cols - 1)
                draw_line(x * 20, y * 20 - map[y][x] * 2, (x + 1) * 20, y * 20 - map[y][x + 1] * 2, mlx_ptr, win_ptr);
            if (y < rows - 1)
                draw_line(x * 20, y * 20 - map[y][x] * 2, x * 20, (y + 1) * 20 - map[y + 1][x] * 2, mlx_ptr, win_ptr);
        }
    }
}

int **read_map(char *filename, int *rows, int *cols)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return NULL;

    char *line = NULL;
    size_t len = 0;
    int y = 0;
    int **map = malloc(sizeof(int*) * 100); // Maximo de 100 linhas

    while (getline(&line, &len, file) != -1)
    {
        map[y] = malloc(sizeof(int) * 100); // Maximo de 100 colunas
        int x = 0;
        char *num = strtok(line, " ");
        while (num)
        {
            map[y][x++] = atoi(num);
            num = strtok(NULL, " ");
        }
        y++;
    }

    *rows = y;
    *cols = 100; // Aqui você pode ajustar se o número de colunas for dinâmico

    free(line);
    fclose(file);

    return map;
}