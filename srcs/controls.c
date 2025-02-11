/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:09:28 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/11 19:24:53 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	verify_redraw(int redraw, t_data *data, t_bound *bound)
{
	if (redraw)
	{
		data->zoom = fmaxf(data->zoom, 0.1);
		data->zoom = fminf(data->zoom, 50.0);
		calculate_projected_bound(data, bound, data->zoom);
		data->offset_x = (WIN_W - (bound->max_x - bound->min_x))
			/ 2 - bound->min_x;
		data->offset_y = (WIN_H - (bound->max_y - bound->min_y))
			/ 2 - bound->min_y;
		draw_map(data);
	}
	return (redraw);
}

int	update_zoom(void *param)
{
	t_data	*data;
	t_bound	bound;
	int		redraw;

	data = (t_data *)param;
	redraw = 0;
	if (data->zoom_in)
	{
		data->zoom *= 1.02;
		redraw = 1;
	}
	if (data->zoom_out)
	{
		data->zoom *= 0.98;
		redraw = 1;
	}
	verify_redraw(redraw, data, &bound);
	return (0);
}

int	handle_key_press(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65307) // ESC
		handle_close(data);
	if (keycode == 65361) // seta esquerda
		data->offset_x += 10;
	if (keycode == 65363) // seta direita
		data->offset_x -= 10;
	if (keycode == 65362) // seta cima
		data->offset_y += 10;
	if (keycode == 65364) // seta baixo
		data->offset_y -= 10;
	if (keycode == 61 || keycode == 65451) // "+"
		data->zoom_in = 1; // Mantém pressionado
	if (keycode == 45 || keycode == 65453) // "-"
		data->zoom_out = 1; // Mantém pressionado
	draw_map(data);
	return (0);
}

int	handle_key_release(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	//Libera apenas quando a tecla específica for solta
	if (keycode == 61 || keycode == 65451)
		data->zoom_in = 0;
	else if (keycode == 45 || keycode == 65453)
		data->zoom_out = 0;
	return (0);
}
