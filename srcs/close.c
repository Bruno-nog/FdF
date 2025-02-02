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

int	handle_key(int keycode, void *param)
{
	if (keycode == 53 || keycode == 65307) // 53 (MacOS) | 65307 (Linux)
		handle_close(param);
	return (0);
}
