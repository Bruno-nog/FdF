#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include "../lib/libft.h"
# include "../minilibx-linux/mlx.h"

# define WIN_WIDTH 1300
# define WIN_HEIGHT 900

typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
    int     **map;
    int     rows;
    int     cols;
    float   zoom;
    int     zoom_in;
    int     zoom_out;
    int     offset_x;
    int     offset_y;
    int     pan_offset_x;  // Adicione esta linha
    int     pan_offset_y;  // E esta
}   t_data;

// Funções principais
int handle_key_release(int keycode, void *param);
int handle_key_press(int keycode, void *param);
int update_zoom(void *param);
int **read_map(char *filename, int *rows, int *cols);
void draw_map(t_data *data);
void draw_line(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr);
int	handle_close(void *param);
void	free_map(int **map, int rows);
void calculate_projected_bounds(t_data *data, int *min_x, int *min_y, int *max_x, int *max_y, float zoom);

//checks
int count_columns(char *line);
int count_rows(FILE *file);
int **allocate_map(int rows, int cols);
void fill_map(FILE *file, int **map, int rows, int cols);
int **read_map(char *filename, int *rows, int *cols);

//projection
void	projection_iso(int *x, int *y, int z);
void draw_line_img(int x1, int y1, int x2, int y2, char *addr, int line_length, int bpp, int endian);
void my_mlx_pixel_put(char *addr, int x, int y, int color, int line_length, int bpp);

#endif
