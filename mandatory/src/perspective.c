/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:37:37 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/23 10:46:59 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to initialize perpsective view values
void    initialize_perspective_view(t_fdf *fdf)
{
    fdf->iso_on = 0;
    fdf->Ox = -0.0764;
    fdf->Oy = 0.6854;
    fdf->Oz = 0;
}

// Function to transform coordonates for a perspective view
void    project_perspective_point(t_point *point, t_fdf *fdf)
{
    t_rotation	rot;
    float   factor;
    
    rot.temp_z = point->z * - fdf->depth;
	rot.x = point->x;
	rot.y = point->y * fdf->cosOx - rot.temp_z * fdf->sinOx;
	rot.z = point->y * fdf->sinOx + rot.temp_z * fdf->cosOx;
	rot.temp_x = rot.x;
	rot.x = rot.temp_x * fdf->cosOy + rot.z * fdf->sinOy;
	rot.z = -rot.temp_x * fdf->sinOy + rot.z * fdf->cosOy;
    rot.temp_x = rot.x;
    rot.temp_y = rot.y;
    rot.x = rot.temp_x * fdf->cosOz - rot.temp_y* fdf->sinOz;
    rot.y = rot.temp_x* fdf->sinOz + rot.temp_y * fdf->cosOz;
    factor = fdf->distance / (fdf->distance + rot.z);
    rot.x_proj = rot.x * factor;
    rot.y_proj = rot.y * factor;
    point->x_out = rot.x_proj * fdf->zoom;
    point->y_out = rot.y_proj * fdf->zoom;
    point->x_out = point->x_out + fdf->originX;
    point->y_out = point->y_out + fdf->originY;
}
