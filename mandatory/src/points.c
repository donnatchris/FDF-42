/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:43:07 by christophed       #+#    #+#             */
/*   Updated: 2025/01/23 01:47:56 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to generate the image
int	render(t_fdf *fdf)
{	
	animation(fdf);
	project_isometric_map(fdf);
	draw_lines(fdf);
	print_menu(fdf);
	return (0);
}

// Function to clear the image
void clear_image(t_fdf *fdf)
{
    ft_printf("clear_image\n");
    int x;
    int y;

    y = 0;
    while (y < fdf->win_height)
    {
        x = 0;
        while (x < fdf->win_width)
        {
            put_pixel_to_image(fdf, x, y, fdf->back_color);
            x++;
        }
        y++;
    }
}

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

// void project_isometric_point(t_point *point, t_fdf *fdf)
// {
//     point->x_out = fdf->originX + fdf->zoom * (point->x - point->y);
//     point->y_out = fdf->originY + fdf->zoom * ((point->x + point->y) / 2 - point->z);
// }

// LAST VERSION
// void    project_isometric_point(t_point *point, t_fdf *fdf)
// {
//     t_rotation	rot;

//     // Appliquer la profondeur
//     rot.temp_z = point->z * fdf->depth;
//     // Step 1: Rotation autour de l'axe X
// 	// Rotation selon X
// 	rot.x = point->x;
// 	rot.y = point->y * cos(fdf->Ox) - rot.temp_z * sin(fdf->Ox);
// 	rot.z = point->y * sin(fdf->Ox) + rot.temp_z * cos(fdf->Ox);
//     // Step 2: Rotation autour de l'axe Y
// 	rot.temp_x = rot.x;
// 	rot.x = rot.temp_x * cos(fdf->Oy) + rot.z * sin(fdf->Oy);
// 	rot.z = -rot.temp_x * sin(fdf->Oy) + rot.z * cos(fdf->Oy);
//     // Step 3: Rotation autour de l'axe Z
//     rot.temp_x = rot.x;
//     rot.temp_y = rot.y;
//     rot.x = rot.temp_x * cos(fdf->Oz) - rot.temp_y* sin(fdf->Oz);
//     rot.y = rot.temp_x* sin(fdf->Oz) + rot.temp_y * cos(fdf->Oz);
//     // Step 4: Projection 3D vers 2D
//     rot.x_proj = 0.866 * rot.x - 0.866 * rot.y;
//     rot.y_proj = 0.5 * rot.x + 0.5 * rot.y - rot.z;
//     // Step 5: Application du zoom
//     point->x_out = rot.x_proj * fdf->zoom;
//     point->y_out = rot.y_proj * fdf->zoom;
//     // Step 6: Après zoom, centrer par rapport à l’écran
//     point->x_out = point->x_out + fdf->originX;
//     point->y_out = point->y_out + fdf->originY;
// }

// PERSPECTIVE
void    project_isometric_point(t_point *point, t_fdf *fdf)
{
    t_rotation	rot;

    // A calculer une seule fois
    float   factor;



    // Appliquer la profondeur
    rot.temp_z = point->z * - fdf->depth;
    // Step 1: Rotation autour de l'axe X
	// Rotation selon X
	rot.x = point->x;
	rot.y = point->y * cos(fdf->Ox) - rot.temp_z * sin(fdf->Ox);
	rot.z = point->y * sin(fdf->Ox) + rot.temp_z * cos(fdf->Ox);
    // Step 2: Rotation autour de l'axe Y
	rot.temp_x = rot.x;
	rot.x = rot.temp_x * cos(fdf->Oy) + rot.z * sin(fdf->Oy);
	rot.z = -rot.temp_x * sin(fdf->Oy) + rot.z * cos(fdf->Oy);
    // Step 3: Rotation autour de l'axe Z
    rot.temp_x = rot.x;
    rot.temp_y = rot.y;
    rot.x = rot.temp_x * cos(fdf->Oz) - rot.temp_y* sin(fdf->Oz);
    rot.y = rot.temp_x* sin(fdf->Oz) + rot.temp_y * cos(fdf->Oz);
    // Step 4: Projection 3D vers 2D
    factor = fdf->distance / (fdf->distance + rot.z);
    rot.x_proj = rot.x * factor;
    rot.y_proj = rot.y * factor;
    // Step 5: Application du zoom
    point->x_out = rot.x_proj * fdf->zoom;
    point->y_out = rot.y_proj * fdf->zoom;
    // Step 6: Après zoom, centrer par rapport à l’écran
    point->x_out = point->x_out + fdf->originX;
    point->y_out = point->y_out + fdf->originY;
}

// Function to print the menu on screen
void	print_menu(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 30, LIGHT_GREEN, "ZOOM: ........ + / -");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 60, LIGHT_GREEN, "DEPTH: ....... Page up / Page down");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 90, LIGHT_GREEN, "MOVE: ........ Arrows");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 120, LIGHT_GREEN, "ROTATE: ...... a / s / d / f");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 150, LIGHT_GREEN, "ROTATE 90: ... r");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 180, LIGHT_GREEN, "BACK TO ISO: . i");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 210, LIGHT_GREEN, "EXIT: ........ esc");
}

