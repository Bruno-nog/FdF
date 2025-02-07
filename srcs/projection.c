/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:03:33 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/07 19:55:16 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	projection_iso(int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;

	*x = (prev_x - prev_y) * 0.866; // cos(30°)
	*y = (prev_x + prev_y) * 0.5 - z; // sin(30°) - altura z
}
#include "../include/fdf.h"

void my_mlx_pixel_put(char *addr, int x, int y, int color, int line_length, int bpp)
{
    // Verifica se o pixel está dentro dos limites da janela
    if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
        return;
    char *dst = addr + (y * line_length + x * (bpp / 8));
    *(unsigned int*)dst = color;
}

void draw_line_img(int x1, int y1, int x2, int y2, char *addr, int line_length, int bpp, int endian)
{
    int dx, dy, sx, sy, err, e2;
    
    (void) endian;  // Suprime o aviso de parâmetro não utilizado

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = (x1 < x2) ? 1 : -1;
    sy = (y1 < y2) ? 1 : -1;
    err = dx - dy;
    
    while (1)
    {
        my_mlx_pixel_put(addr, x1, y1, 0xFFFFFF, line_length, bpp);
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
