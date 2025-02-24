/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:31:44 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/20 16:06:19 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	verify_argc_and_readmap(int argc, char **argv, t_data *data)
{
	if (argc != 2)
	{
		write(1, "Usage: ./fdf [mapfile]\n", 23);
		return (1);
	}
	data->map = read_map(argv[1], &data->rows, &data->cols);
	if (!data->map)
	{
		write(1, "Error reading map file.\n", 24);
		return (1);
	}
	return (0);
}

static void	assignment_zoom_offset(t_data *data)
{
	data->zoom = 1.0;
	data->zoom_in = 0;
	data->zoom_out = 0;
	data->offset_x = 0;
	data->offset_y = 0;
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_bound		bound;
	float		width_ratio;
	float		height_ratio;

	if (verify_argc_and_readmap (argc, argv, &data) == 1)
		return (1);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, "FdF");
	assignment_zoom_offset (&data);
	calculate_projected_bound(&data, &bound, data.zoom);
	width_ratio = (WIN_W - 40) / (float)(bound.max_x - bound.min_x);
	height_ratio = (WIN_H - 40) / (float)(bound.max_y - bound.min_y);
	data.zoom = fminf(width_ratio, height_ratio);
	data.zoom = fmaxf(data.zoom, 0.1);
	calculate_projected_bound(&data, &bound, data.zoom);
	data.offset_x = (WIN_W - (bound.max_x - bound.min_x)) / 2 - bound.min_x;
	data.offset_y = (WIN_H - (bound.max_y - bound.min_y)) / 2 - bound.min_y;
	draw_map(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, handle_key_release, &data);
	mlx_hook(data.win_ptr, 17, 0, handle_close, &data);
	mlx_loop_hook(data.mlx_ptr, update_zoom, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
