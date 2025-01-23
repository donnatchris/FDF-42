/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:37:37 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/23 16:48:38 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to initialize perpsective view values
void    initialize_perspective_view(t_fdf *fdf)
{
    fdf->iso_on = 0;
    fdf->ox = -0.0764;
    fdf->oy = 0.6854;
    fdf->oz = 0;
}

// Function to transform coordonates for a perspective view
void    project_perspective_point(t_point *point, t_fdf *fdf)
{
    t_rotation	rot;
    float   factor;
    
    rot.temp_z = point->z * - fdf->depth;
	rot.x = point->x;
	rot.y = point->y * fdf->cosox - rot.temp_z * fdf->sinox;
	rot.z = point->y * fdf->sinox + rot.temp_z * fdf->cosox;
	rot.temp_x = rot.x;
	rot.x = rot.temp_x * fdf->cosoy + rot.z * fdf->sinoy;
	rot.z = -rot.temp_x * fdf->sinoy + rot.z * fdf->cosoy;
    rot.temp_x = rot.x;
    rot.temp_y = rot.y;
    rot.x = rot.temp_x * fdf->cosoz - rot.temp_y* fdf->sinoz;
    rot.y = rot.temp_x* fdf->sinoz + rot.temp_y * fdf->cosoz;
    factor = fdf->distance / (fdf->distance + rot.z);
    rot.x_proj = rot.x * factor;
    rot.y_proj = rot.y * factor;
    point->x_out = rot.x_proj * fdf->zoom;
    point->y_out = rot.y_proj * fdf->zoom;
    point->x_out = point->x_out + fdf->originx;
    point->y_out = point->y_out + fdf->originy;
}
