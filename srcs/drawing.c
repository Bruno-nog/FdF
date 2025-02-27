/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:03:33 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/27 11:02:55 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	my_mlx_pixel_put(t_pixel *pixel, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	dst = pixel->addr + (y * pixel->line_length + x * (pixel->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	update_line_vars(t_line_vars *vars, int *x, int *y)
{
	if (vars->e2 > -vars->dy)
	{
		vars->err -= vars->dy;
		*x += vars->sx;
	}
	if (vars->e2 < vars->dx)
	{
		vars->err += vars->dx;
		*y += vars->sy;
	}
}

void	draw_line_img(t_point p1, t_point p2, t_img *img)
{
	t_pixel		pixel;
	t_line		line;
	t_line_vars	vars;
	int			x;
	int			y;

	pixel.addr = img->addr;
	pixel.line_length = img->line_length;
	pixel.bpp = img->bpp;
	line.x1 = p1.x;
	line.y1 = p1.y;
	line.x2 = p2.x;
	line.y2 = p2.y;
	x = line.x1;
	y = line.y1;
	calculate_line_vars(&line, &vars);
	while (1)
	{
		my_mlx_pixel_put(&pixel, x, y, 0x5fa6c1);
		if (x == line.x2 && y == line.y2)
			break ;
		vars.e2 = 2 * vars.err;
		update_line_vars(&vars, &x, &y);
	}
}

void	calculate_line_vars(t_line *line, t_line_vars *vars)
{
	vars->dx = abs(line->x2 - line->x1);
	vars->dy = abs(line->y2 - line->y1);
	if (line->x1 < line->x2)
		vars->sx = 1;
	else
		vars->sx = -1;
	if (line->y1 < line->y2)
		vars->sy = 1;
	else
		vars->sy = -1;
	vars->err = vars->dx - vars->dy;
}

void	draw_map(t_data *data)
{
	t_draw	draw;

	draw.img.img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	draw.img.addr = mlx_get_data_addr(draw.img.img, &draw.img.bpp,
			&draw.img.line_length, &draw.img.endian);
	draw.row = 0;
	while (draw.row < data->rows)
	{
		draw.col = 0;
		while (draw.col < data->cols)
		{
			draw.world1.x = draw.col * 20 * data->zoom;
			draw.world1.y = draw.row * 20 * data->zoom - data->map
			[draw.row][draw.col] * 2 * data->zoom;
			projection_iso(&draw.world1.x, &draw.world1.y,
				data->map[draw.row][draw.col]);
			draw.p1.x = draw.world1.x + data->offset_x;
			draw.p1.y = draw.world1.y + data->offset_y;
			render_map_edges(&draw, data);
			draw.col++;
		}
		draw.row++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, draw.img.img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, draw.img.img);
}
