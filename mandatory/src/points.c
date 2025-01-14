/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:43:07 by christophed       #+#    #+#             */
/*   Updated: 2025/01/14 10:56:23 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

#include "../include/fdf.h"

// Function to draw lines
// void bresenham(t_fdf *fdf, int x0, int y0, int x1, int y1, int color)
// {
//     int dx = abs(x1 - x0);
//     int dy = abs(y1 - y0);
//     int sx = (x0 < x1) ? 1 : -1; // Direction en x
//     int sy = (y0 < y1) ? 1 : -1; // Direction en y
//     int err = dx - dy;           // Erreur initiale

//     while (1)
//     {
//         my_mlx_pixel_put(fdf, x0, y0, color); // Dessiner le pixel
//         if (x0 == x1 && y0 == y1)             // Si on atteint la fin de la ligne
//             break;

//         int e2 = 2 * err;
//         if (e2 > -dy) {
//             err -= dy;
//             x0 += sx;
//         }
//         if (e2 < dx) {
//             err += dx;
//             y0 += sy;
//         }
//     }
// }

// Function to project the points from 3D to 2D by isometric view
void project_isometric_point(t_point *point, int width, int height, int zoom)
{
    ft_printf("project_isometric_point\n");
    const double angle = M_PI / 6;
    const double cos_angle = cos(angle);
    const double sin_angle = sin(angle);
    int           x;
    int           y;
    int           z;

    x = point->x * zoom;
    y = point->y * zoom;
    z = point->z * zoom;
    point->x_out = (x - y) * cos_angle + (width / 2);
    point->y_out = (x + y) * sin_angle - z + (height / 2);
}

// Function to generate x_out and y_out
void    project_isometric_map(t_fdf *fdf)
{
    ft_printf("project_isometric_map\n");
    int i;

    i = 0;
    while(fdf->point[i])
    {
        project_isometric_point(fdf->point[i], fdf->win_width, fdf->win_height, fdf->zoom);
        printf("Point %d : x_out = %.2f, y_out = %.2f\n", i, fdf->point[i]->x_out, fdf->point[i]->y_out);
        i++;
    }
}

// *x_out += SCREEN_WIDTH / 2;
// *y_out += SCREEN_HEIGHT / 2;

// int scale = 10; // Exemple : zoom
// *x_out *= scale;
// *y_out *= scale;