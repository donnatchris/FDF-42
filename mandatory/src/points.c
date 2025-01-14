/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:43:07 by christophed       #+#    #+#             */
/*   Updated: 2025/01/14 13:30:56 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to project the points from 3D to 2D by isometric view
void project_isometric_point(t_point *point, int width, int height, int zoom, int depth)
{
    ft_printf("project_isometric_point\n");
    const double	angle = M_PI / 6;
    const double	cos_angle = cos(angle);
    const double	sin_angle = sin(angle);
    int				x;
    int				y;
    int				z;

    x = point->x * zoom;
    y = point->y * zoom;
    if (point->z != 0)
        z = (point->z * depth) * zoom;
    else
        z = point->z * zoom;
    point->x_out = (x - y) * cos_angle + (width / 2);
    point->y_out = (x + y) * sin_angle - (z) + (height / 2);
}

// Function to generate x_out and y_out
void    project_isometric_map(t_fdf *fdf)
{
    ft_printf("project_isometric_map\n");
    int i;

    i = 0;
    while(fdf->point[i])
    {
        project_isometric_point(fdf->point[i], fdf->win_width, fdf->win_height, fdf->zoom, fdf->depth);
        printf("Point %d : x_out = %.2f, y_out = %.2f\n", i, fdf->point[i]->x_out, fdf->point[i]->y_out);
        i++;
    }
}

// *x_out += SCREEN_WIDTH / 2;
// *y_out += SCREEN_HEIGHT / 2;

// int scale = 10; // Exemple : zoom
// *x_out *= scale;
// *y_out *= scale;