#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "../lib/libft.h"
# include "../minilibx-linux/mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		**map;
	int		rows;
	int		cols;
}	t_data;

// Funções principais
int	**read_map(char *filename, int *rows, int *cols);
void draw_map(int **map, int rows, int cols, void *mlx_ptr, void *win_ptr);

// Funções auxiliares
void	draw_line(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr);

// close windows functions
void	free_map(int **map, int rows);
int		handle_close(void *param);
int		handle_key(int keycode, void *param);

//projection "3d"
void	projection_iso(int *x, int *y, int z);


#endif
