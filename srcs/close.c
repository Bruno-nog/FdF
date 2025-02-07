/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:19:54 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/06 18:28:01 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_map(int **map, int rows)
{
	int	i;

	for (i = 0; i < rows; i++)
		free(map[i]);
	free(map);
}

int	handle_close(void *param)
{ 
	t_data	*data;

	data = (t_data *)param;
	free_map(data->map, data->rows);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}