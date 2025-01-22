/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:43:07 by christophed       #+#    #+#             */
/*   Updated: 2025/01/22 17:56:53 by christophed      ###   ########.fr       */
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



// OLD ISO - view ok but not rotation
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

// GPT ISO - rotation ok but not view
// Function to project the points from 3D to 2D
// using an isometric projection with rotation
void project_isometric_point(t_point *point, t_fdf *fdf)
{
    float x, y, z;
    float x_rot, y_rot, z_rot;

    // Appliquer le décalage vers le centre et la profondeur
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

// typedef struct	s_projection
// {
// 	float	x_rot;
// 	float	y_rot;
// 	float	z_rot;
// 	float	temp_x_rot;
// }				t_projection;

// // TEST ISO
// void	project_isometric_point(t_point *point, t_fdf *fdf)
// {
// 	t_projection	proj;

// 	// Appliquer le décalage vers le centre
//     point->x = point->x - fdf->x_mid;
//     point->y = point->y - fdf->y_mid;
//     point->z = point->z * fdf->depth;

// 	// Rotation selon X
// 	proj.x_rot = point->x;
// 	proj.y_rot = point->y * cos(fdf->Ox) - point->z * sin(fdf->Ox);
// 	proj.z_rot = point->y * sin(fdf->Ox) + point->z * cos(fdf->Ox);

// 	// Rotation selon Y
// 	proj.temp_x_rot = proj.x_rot; // Sauvegarder pour éviter un écrasement immédiat
// 	proj.x_rot = proj.temp_x_rot * cos(fdf->Oy) + proj.z_rot * sin(fdf->Oy);
// 	proj.z_rot = -proj.temp_x_rot * sin(fdf->Oy) + proj.z_rot * cos(fdf->Oy);

// 	// Projection isométrique
// 	point->x_out = 0.866 * proj.x_rot - 0.866 * proj.y_rot;
// 	point->y_out = 0.5 * proj.x_rot + 0.5 * proj.y_rot - proj.z_rot;

// }

typedef struct	s_rotation
{
	float	x;
	float	y;
	float	z;
	float	temp_x;
}				t_rotation;

// TEST ISO
void	project_isometric_point(t_point *point, t_fdf *fdf)
{
	t_rotation	rot;

	// Appliquer le décalage vers le centre
	// ATTENTION A APPLIQUER UNE FOIS DANS L INITIALISATION ET PLUS PAR LA SUITE
    point->x = point->x - fdf->x_mid;
    point->y = point->y - fdf->y_mid;

	// Appliquer la profondeur
    point->z = point->z * fdf->depth;

	// Rotation selon X
	rot.x = point->x;
	rot.y = point->y * cos(fdf->Ox) - point->z * sin(fdf->Ox);
	rot.z = point->y * sin(fdf->Ox) + point->z * cos(fdf->Ox);

	// Rotation selon Y
	rot.temp_x = rot.x;
	rot.x = rot.temp_x * cos(fdf->Oy) + rot.z * sin(fdf->Oy);
	rot.z = -rot.temp_x * sin(fdf->Oy) + rot.z * cos(fdf->Oy);

	// Projection isométrique
	point->x_out = fdf->originX + fdf->factor * (0.866 * rot.x - 0.866 * rot.y);
	point->y_out = fdf->originY + fdf->factor * (0.5 * rot.x + 0.5 * rot.y - rot.z);

	// Projection oblique
	point->x_out = fdf->originX + fdf->factor * (rot.x + 0.5 * rot.z);
	point->y_out = fdf->originY + fdf->factor * (rot.y + 0.5 * rot.z);
}

