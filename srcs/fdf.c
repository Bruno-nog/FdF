/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:19:50 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/03 16:15:47 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	draw_line(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr)
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


void	draw_map(int **map, int rows, int cols, void *mlx_ptr, void *win_ptr)
{
	int	x, y;
	int	x1, y1, x2, y2;

	for (y = 0; y < rows; y++)
	{
		for (x = 0; x < cols; x++)
		{
			// Aplica a projeção isométrica para o ponto (x, y, z)
			x1 = x * 20;
			y1 = y * 20 - map[y][x] * 2;
			projection_iso(&x1, &y1, map[y][x]);  // Aqui os valores de x1 e y1 são alterados

			// Conecta os pontos adjacentes
			if (x < cols - 1)
			{
				x2 = (x + 1) * 20;
				y2 = y * 20 - map[y][x + 1] * 2;
				projection_iso(&x2, &y2, map[y][x + 1]);  // Projeção isométrica aplicada a x2, y2
				draw_line(x1, y1, x2, y2, mlx_ptr, win_ptr);
			}

			if (y < rows - 1)
			{
				x2 = x * 20;
				y2 = (y + 1) * 20 - map[y + 1][x] * 2;
				projection_iso(&x2, &y2, map[y + 1][x]);  // Projeção isométrica aplicada a x2, y2
				draw_line(x1, y1, x2, y2, mlx_ptr, win_ptr);
			}
		}
	}
}



int	**read_map(char *filename, int *rows, int *cols)
{
	FILE	*file;
	char	*line;
	size_t	len;
	int		y;
	int		**map;
	char	*num;
	int		x;

	file = fopen(filename, "r");
	if (!file)
		return (NULL);
	map = malloc(sizeof(int *) * 100);
	y = 0;
	while (getline(&line, &len, file) != -1)
	{
		map[y] = malloc(sizeof(int) * 100);
		x = 0;
		num = strtok(line, " ");
		while (num)
		{
			map[y][x++] = atoi(num);
			num = strtok(NULL, " ");
		}
		y++;
	}
	*rows = y;
	*cols = 100;
	free(line);
	fclose(file);
	return (map);
}
