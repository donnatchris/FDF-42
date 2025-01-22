/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:43:07 by christophed       #+#    #+#             */
/*   Updated: 2025/01/22 10:57:48 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to generate x_out and y_out
void    project_isometric_map(t_fdf *fdf)
{
    int i;
    
    fill_color(fdf);
    i = 0;
    while(fdf->point[i])
    {
        project_isometric_point(fdf->point[i], fdf);
        i++;
    }

}




// Function to project the points from 3D to 2D
// using a isometric projection
// void	project_isometric_point(t_point *point, t_fdf *fdf)
// {
//     float   x;
//     float	y;
//     float	z;

//     x = point->x - fdf->x_mid;
//     y = point->y - fdf->y_mid;
//     z = point->z * fdf->depth;
//     point->x_out = fdf->originX + fdf->factor * (x * cos(fdf->Ox) - y * cos(fdf->Oy));
//     point->y_out = fdf->originY + fdf->factor * (x * sin(fdf->Ox) + y * sin(fdf->Oy) - z);
// }


// Function to project the points from 3D to 2D
// using an isometric projection with rotation
void project_isometric_point(t_point *point, t_fdf *fdf)
{
    float x, y, z;
    float x_rot, y_rot, z_rot;

    // Appliquer le décalage vers le centre
    x = point->x - fdf->x_mid;
    y = point->y - fdf->y_mid;
    z = point->z * fdf->depth;

    // Appliquer les rotations autour des axes X et Y
    // Rotation autour de l'axe X (Ox)
    x_rot = x;
    y_rot = y * cos(fdf->Ox) - z * sin(fdf->Ox);
    z_rot = y * sin(fdf->Ox) + z * cos(fdf->Ox);

    // Rotation autour de l'axe Y (Oy)
    x = x_rot * cos(fdf->Oy) + z_rot * sin(fdf->Oy);
    y = y_rot;
    z = -x_rot * sin(fdf->Oy) + z_rot * cos(fdf->Oy);

    // Projection isométrique sur les axes X et Y
    point->x_out = fdf->originX + fdf->factor * (x * cos(0.7854) - y * cos(0.6155));
    point->y_out = fdf->originY + fdf->factor * (x * sin(0.7854) + y * sin(0.6155) - z);
    // point->x_out = fdf->originX + fdf->factor * (x  - y);
    // point->y_out = fdf->originY + fdf->factor * (x  + y - z);
}



