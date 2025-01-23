/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:37:56 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/23 14:34:38 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to initialize isometric view values
void    initialize_isometric_view(t_fdf *fdf)
{
    fdf->iso_on = 1; 
    fdf->Ox = 0;
    fdf->Oy = 0;
    fdf->Oz = 0;
}

// Function to transform coordonates for an isometric view
void    project_isometric_point(t_point *point, t_fdf *fdf)
{
    t_rotation	rot;

    rot.temp_z = point->z * fdf->depth;
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
    rot.x_proj = 0.866 * (rot.x - rot.y);
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
/*
# define ANG_1				0.01745329
# define ANG_30				0.52359877
# define ANG_45				0.78539816

Pour ANG_1 (environ 1°) :

cos ≈ 0.9998477
sin ≈ 0.0174524
Pour ANG_30 (30°) :

cos ≈ 0.8660254
sin ≈ 0.5
Pour ANG_45 (45°) :

cos ≈ 0.7071068
sin ≈ 0.7071068
*/

