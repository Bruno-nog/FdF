/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:16:17 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/11 19:45:20 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	projection_iso(int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * 0.866;
	*y = (prev_x + prev_y) * 0.5 - z;
}

void	render_map_edges(t_draw *draw, t_data *data)
{
	draw->data = data;
	if (draw->col < draw->data->cols - 1)
		render_horizontal_edge(draw, data);
	if (draw->row < draw->data->rows - 1)
		render_vertical_edge(draw, data);
}

void	render_horizontal_edge(t_draw *draw, t_data *data)
{
	draw->world2.x = (draw->col + 1) * 20 * data->zoom;
	draw->world2.y = draw->row * 20 * data->zoom - data->map
	[draw->row][draw->col + 1] * 2 * data->zoom;
	projection_iso(&draw->world2.x, &draw->world2.y,
		data->map[draw->row][draw->col + 1]);
	draw->p2.x = draw->world2.x + data->offset_x;
	draw->p2.y = draw->world2.y + data->offset_y;
	draw_line_img((t_point){draw->p1.x, draw->p1.y},
		(t_point){draw->p2.x, draw->p2.y}, &draw->img);
}

void	render_vertical_edge(t_draw *draw, t_data *data)
{
	draw->world2.x = draw->col * 20 * data->zoom;
	draw->world2.y = (draw->row + 1) * 20 * data->zoom - data->map
	[draw->row + 1][draw->col] * 2 * data->zoom;
	projection_iso(&draw->world2.x, &draw->world2.y,
		data->map[draw->row + 1][draw->col]);
	draw->p2.x = draw->world2.x + data->offset_x;
	draw->p2.y = draw->world2.y + data->offset_y;
	draw_line_img((t_point){draw->p1.x, draw->p1.y},
		(t_point){draw->p2.x, draw->p2.y}, &draw->img);
}
