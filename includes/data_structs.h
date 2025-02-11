/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:25:28 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/11 19:36:16 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTS_H
# define DATA_STRUCTS_H

# include "fdf.h"

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		**map;
	int		rows;
	int		cols;
	float	zoom;
	int		zoom_in;
	int		zoom_out;
	int		offset_x;
	int		offset_y;
	int		pan_offset_x;
	int		pan_offset_y;
}	t_data;

typedef struct s_bound
{
	int	min_x;
	int	min_y;
	int	max_x;
	int	max_y;
}	t_bound;

#endif