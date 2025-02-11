/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:25:53 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/11 19:36:06 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_STRUCTS_H
# define DRAW_STRUCTS_H

# include "fdf.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_pixel
{
	char	*addr;
	int		line_length;
	int		bpp;
}	t_pixel;

typedef struct s_line
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}	t_line;

#endif