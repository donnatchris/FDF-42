/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:14:10 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/20 14:59:17 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to affect a color to all points
void	fill_color(t_fdf *fdf)
{
	int i;

	i = 0;
	while (fdf->point[i])
	{
		fdf->point[i]->color = color_manager(fdf->point[i]->z, fdf);
		i++;
	}
}

// Function to affect a color to a point depending on its altitude
int	color_manager(float z, t_fdf *fdf)
{
    double t;

    if (z == 0)
        return (fdf->zero_color);
    if (z == fdf->z_max)
        return (fdf->up_color);
    t = (double)z / fdf->z_max;
    if (z > 0)
        return (interpolate_color(fdf->zero_color, fdf->up_color, t));
    else
    {
        t = -t;
        return (interpolate_color(fdf->zero_color, fdf->low_color, t));
    }
}

// Function to interpolate between two colors
int	interpolate_color(int color1, int color2, double t)
{
    t_color rgb;

    rgb.r1 = (color1 >> 16) & 0xFF;
    rgb.g1 = (color1 >> 8) & 0xFF;
    rgb.b1 = color1 & 0xFF;
    rgb.r2 = (color2 >> 16) & 0xFF;
    rgb.g2 = (color2 >> 8) & 0xFF;
    rgb.b2 = color2 & 0xFF;
    rgb.r = rgb.r1 + t * (rgb.r2 - rgb.r1);
    rgb.g = rgb.g1 + t * (rgb.g2 - rgb.g1);
    rgb.b = rgb.b1 + t * (rgb.b2 - rgb.b1);
    return (rgb.r << 16) | (rgb.g << 8) | rgb.b;
}

// Function to have some fun
void	animate_colors(t_fdf *fdf)
{
    int i;
    int j;

    j = 0;
    if (!fdf->anim_on)
        return ;
    // mlx_loop_end(fdf);
    while (j < 4)
    {
        i = 0;
        while (i++ < 4)
        {
            swap_colors(&fdf->back_color, &fdf->zero_color);
            project_isometric_map(fdf);
            draw_lines(fdf);
            // print_menu(fdf);
            usleep(500000);
        }
        i = 0;
        while (i++ < 10)
        {
            swap_colors(&fdf->up_color, &fdf->low_color);
            project_isometric_map(fdf);
            draw_lines(fdf);
            // print_menu(fdf);
            usleep(100000);
        }
        i = 0;
        while (i++ < 4)
        {
            swap_colors(&fdf->back_color, &fdf->zero_color);
            project_isometric_map(fdf);
            draw_lines(fdf);
            // print_menu(fdf);
            usleep(500000);
        }
        i = 0;
        while (i++ < 4)
        {
            swap_colors(&fdf->up_color, &fdf->zero_color);
            project_isometric_map(fdf);
            draw_lines(fdf);
            // print_menu(fdf);
            usleep(100000);
            swap_colors(&fdf->zero_color, &fdf->low_color);
            project_isometric_map(fdf);
            draw_lines(fdf);
            // print_menu(fdf);
            usleep(100000);
            swap_colors(&fdf->low_color, &fdf->back_color);
            project_isometric_map(fdf);
            draw_lines(fdf);
            // print_menu(fdf);
            usleep(100000);
            swap_colors(&fdf->back_color, &fdf->up_color);
            project_isometric_map(fdf);
            draw_lines(fdf);
            // print_menu(fdf);
            usleep(100000);
        }
    }

}