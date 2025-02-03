/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:31:44 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/03 14:08:17 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int argc, char **argv)
{
	t_data	data;

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

	draw_map(data.map, data.rows, data.cols, data.mlx_ptr, data.win_ptr);

	mlx_hook(data.win_ptr, 17, 0, handle_close, &data); // Botão X
	mlx_key_hook(data.win_ptr, handle_key, &data); // Tecla Esc

	mlx_loop(data.mlx_ptr);
	return (0);
}
