/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_structs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:26:30 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/11 19:36:21 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTION_STRUCTS_H
# define PROJECTION_STRUCTS_H

# include "fdf.h"

typedef struct s_line_vars
{
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	dx;
	int	dy;
}	t_line_vars;

#endif