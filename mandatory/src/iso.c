/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:37:56 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/23 09:39:54 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to transform coordonates for an isometric view
void    project_isometric_point(t_point *point, t_fdf *fdf)
{
    t_rotation	rot;

    rot.temp_z = point->z * fdf->depth;
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
    rot.x_proj = 0.866 * rot.x - 0.866 * rot.y;
    rot.y_proj = 0.5 * rot.x + 0.5 * rot.y - rot.z;
    point->x_out = rot.x_proj * fdf->zoom;
    point->y_out = rot.y_proj * fdf->zoom;
    point->x_out = point->x_out + fdf->originX;
    point->y_out = point->y_out + fdf->originY;
}

// void project_isometric_point(t_point *point, t_fdf *fdf)
// {
//     point->x_out = fdf->originX + fdf->zoom * (point->x - point->y);
//     point->y_out = fdf->originY + fdf->zoom * ((point->x + point->y) / 2 - point->z);
// }

