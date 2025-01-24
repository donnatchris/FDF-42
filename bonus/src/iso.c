/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:37:56 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/24 10:05:50 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to initialize isometric view values
void	initialize_isometric_view(t_fdf *fdf)
{
	fdf->iso_on = 1;
	fdf->ox = 0;
	fdf->oy = 0;
	fdf->oz = 0;
}

// Function to transform coordonates for an isometric view
void	project_isometric_point(t_point *point, t_fdf *fdf)
{
	t_rotation	rot;

	rot.temp_z = point->z * fdf->depth;
	rot.x = point->x;
	rot.y = point->y * fdf->cosox - rot.temp_z * fdf->sinox;
	rot.z = point->y * fdf->sinox + rot.temp_z * fdf->cosox;
	rot.temp_x = rot.x;
	rot.x = rot.temp_x * fdf->cosoy + rot.z * fdf->sinoy;
	rot.z = -rot.temp_x * fdf->sinoy + rot.z * fdf->cosoy;
	rot.temp_x = rot.x;
	rot.temp_y = rot.y;
	rot.x = rot.temp_x * fdf->cosoz - rot.temp_y * fdf->sinoz;
	rot.y = rot.temp_x * fdf->sinoz + rot.temp_y * fdf->cosoz;
	rot.x_proj = 0.866 * (rot.x - rot.y);
	rot.y_proj = 0.5 * rot.x + 0.5 * rot.y - rot.z;
	point->x_out = rot.x_proj * fdf->zoom;
	point->y_out = rot.y_proj * fdf->zoom;
	point->x_out = point->x_out + fdf->originx;
	point->y_out = point->y_out + fdf->originy;
}
