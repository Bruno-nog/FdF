/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:26:12 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/11 19:36:18 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_STRUCTS_H
# define MAP_STRUCTS_H

# include "fdf.h"

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_draw
{
	int		row;
	int		col;
	t_data	*data;
	t_coord	p1;
	t_coord	p2;
	t_coord	world1;
	t_coord	world2;
	t_img	img;
}	t_draw;

#endif