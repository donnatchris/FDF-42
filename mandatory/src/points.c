/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:43:07 by christophed       #+#    #+#             */
/*   Updated: 2025/01/22 09:06:22 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to generate x_out and y_out
void    project_isometric_map(t_fdf *fdf)
{
    // ft_printf("project_isometric_map\n");
    int i;
    
    fill_color(fdf);
    i = 0;
    while(fdf->point[i])
    {
        project_isometric_point(fdf->point[i], fdf);
        // project_perspective_point(fdf->point[i], fdf);
        i++;
    }

}

// Function to project the points from 3D to 2D
// using a perspective projection
void	project_perspective_point(t_point *point, t_fdf *fdf)
{
	float	x;
    float	y;
    float	z;
	float	x_rot;
	float	y_rot;
	float	z_rot;

	fdf->distance = 100;
	x = point->x;
    y = point->y;
    z = (point->z * fdf->depth);
	y_rot = y * cos(fdf->Ox) - z * sin(fdf->Ox);
    z_rot = y * sin(fdf->Ox) + z * cos(fdf->Ox);
    x_rot = x * cos(fdf->Oy) + z_rot * sin(fdf->Oy);
    z_rot = -x * sin(fdf->Oy) + z_rot * cos(fdf->Oy);
    point->x_out = fdf->originX + fdf->factor * (x_rot * fdf->distance) / (y_rot + fdf->distance);
    point->y_out = fdf->originY + fdf->factor * (z_rot * fdf->distance) / (y_rot + fdf->distance);
}


// Function to project the points from 3D to 2D
// using a isometric projection
void	project_isometric_point(t_point *point, t_fdf *fdf)
{
    float   x;
    float	y;
    float	z;

    x = point->x - fdf->x_mid;
    y = point->y - fdf->y_mid;
    z = point->z * fdf->depth;
    point->x_out = fdf->originX + fdf->factor * (x * cos(fdf->Ox) - y * cos(fdf->Oy));
    point->y_out = fdf->originY + fdf->factor * (x * sin(fdf->Ox) + y * sin(fdf->Oy) - z);
}
