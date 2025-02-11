/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:33:13 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/11 19:42:20 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include "../lib/libft.h"
# include "../minilibx-linux/mlx.h"
//HEADERS 
# include "data_structs.h"
# include "draw_structs.h"
# include "map_structs.h"
# include "projection_structs.h"

# define WIN_W 1200
# define WIN_H 900

//FDF
void	calculate_projected_bound(t_data *data, t_bound *bound, float zoom);
//DRAWING
void	draw_map(t_data *data);
void	render_map_edges(t_draw *draw, t_data *data);
void	draw_line(t_line line, void *mlx_ptr, void *win_ptr);
void	my_mlx_pixel_put(t_pixel *pixel, int x, int y, int color);
void	calculate_line_vars(t_line *line, t_line_vars *vars);
void	draw_line_img(t_point p1, t_point p2, t_img *img);
//FILE PARSER
int		count_columns(char *line);
int		count_rows(FILE *file);
int		**allocate_map(int rows, int cols);
void	fill_map(FILE *file, int **map, int x, int cols);
int		**read_map(char *filename, int *rows, int *cols);
//PROJECTION
void	projection_iso(int *x, int *y, int z);
void	render_horizontal_edge(t_draw *draw, t_data *data);
void	render_vertical_edge(t_draw *draw, t_data *data);

//CONTROLS
int		handle_key_release(int keycode, void *param);
int		handle_key_press(int keycode, void *param);
int		update_zoom(void *param);
int		verify_redraw(int redraw, t_data *data, t_bound *bound);
//CLOSE
void	free_map(int **map, int rows);
int		handle_close(void *param);

#endif
