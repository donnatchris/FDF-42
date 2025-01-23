/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:37:37 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/23 09:39:39 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to transform coordonates for a perspective view
void    project_perspective_point(t_point *point, t_fdf *fdf)
{
    t_rotation	rot;
    // A calculer une seule fois
    float   factor;
    
    rot.temp_z = point->z * - fdf->depth;
	rot.x = point->x;
	rot.y = point->y * cos(fdf->Ox) - rot.temp_z * sin(fdf->Ox);
	rot.z = point->y * sin(fdf->Ox) + rot.temp_z * cos(fdf->Ox);
	rot.temp_x = rot.x;
	rot.x = rot.temp_x * cos(fdf->Oy) + rot.z * sin(fdf->Oy);
	rot.z = -rot.temp_x * sin(fdf->Oy) + rot.z * cos(fdf->Oy);
    rot.temp_x = rot.x;
    rot.temp_y = rot.y;
    rot.x = rot.temp_x * cos(fdf->Oz) - rot.temp_y* sin(fdf->Oz);
    rot.y = rot.temp_x* sin(fdf->Oz) + rot.temp_y * cos(fdf->Oz);
    factor = fdf->distance / (fdf->distance + rot.z);
    rot.x_proj = rot.x * factor;
    rot.y_proj = rot.y * factor;
    point->x_out = rot.x_proj * fdf->zoom;
    point->y_out = rot.y_proj * fdf->zoom;
    point->x_out = point->x_out + fdf->originX;
    point->y_out = point->y_out + fdf->originY;
}