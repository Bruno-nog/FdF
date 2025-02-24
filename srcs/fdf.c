/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:19:50 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/24 20:41:02 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	set_step_values(t_line line, int *sx, int *sy)
{
	if (line.x1 < line.x2)
		*sx = 1;
	else
		*sx = -1;
	if (line.y1 < line.y2)
		*sy = 1;
	else
		*sy = -1;
}

void	draw_line(t_line line, void *mlx_ptr, void *win_ptr)
{
	int	step_values[4];
	int	error;
	int	e2;

	step_values[0] = abs(line.x2 - line.x1);
	step_values[1] = abs(line.y2 - line.y1);
	set_step_values(line, &step_values[2], &step_values[3]);
	error = step_values[0] - step_values[1];
	while (1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, line.x1, line.y1, 0xFFFFFF);
		if (line.x1 == line.x2 && line.y1 == line.y2)
			break ;
		e2 = 2 * error;
		if (e2 > -step_values[1])
		{
			error -= step_values[1];
			line.x1 += step_values[2];
		}
		if (e2 < step_values[0])
		{
			error += step_values[0];
			line.y1 += step_values[3];
		}
	}
}

static void	update_bounds(t_bound *bound, int wx, int wy)
{
	if (wx < bound->min_x)
		bound->min_x = wx;
	if (wx > bound->max_x)
		bound->max_x = wx;
	if (wy < bound->min_y)
		bound->min_y = wy;
	if (wy > bound->max_y)
		bound->max_y = wy;
}

void	calculate_projected_bound(t_data *data, t_bound *bound, float zoom)
{
	int	y;
	int	x;
	int	wx;
	int	wy;

	bound->min_x = INT_MAX;
	bound->min_y = INT_MAX;
	bound->max_x = INT_MIN;
	bound->max_y = INT_MIN;
	y = 0;
	while (y < data->rows)
	{
		x = 0;
		while (x < data->cols)
		{
			wx = x * 20 * zoom;
			wy = y * 20 * zoom;
			projection_iso(&wx, &wy, data->map[y][x]);
			update_bounds(bound, wx, wy);
			x++;
		}
		y++;
	}
}

int	**allocate_map(int rows, int cols)
{
	int	**map;
	int	i;

	map = malloc(sizeof(int *) * rows);
	if (!map)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		map[i] = calloc(cols, sizeof(int));
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}
