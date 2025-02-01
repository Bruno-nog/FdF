#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "../lib/libft.h"
# include "../minilibx-linux/mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

// Funções principais
void draw_map(int **map, int rows, int cols, void *mlx_ptr, void *win_ptr);
int **read_map(char *filename, int *rows, int *cols);

// Funções auxiliares
void draw_line(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr);

#endif
