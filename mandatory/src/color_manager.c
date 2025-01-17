/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:14:10 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/17 17:53:37 by chdonnat         ###   ########.fr       */
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
		fdf->point[i]->color = color_manager(fdf->point[i]->z * fdf->depth, fdf);
		i++;
	}
}

// Function to affect a color to a point depending on its altitude
int	color_manager(int z, t_fdf *fdf)
{
    double t;

    if (z == 0)
        return (WHITE);
    if (z == fdf->z_max)
        return (DARK_GREEN);
    t = (double)z / fdf->z_max;
    if (z > 0)
        return (interpolate_color(WHITE, DARK_GREEN, t));
    else
        return (interpolate_color(WHITE, DARK_RED, t));
}

// Function to interpolate between two colors
int	interpolate_color(int color1, int color2, double t)
{
    int r1;
    int g1;
    int b1;
    int r2;
    int g2;
    int b2;
    int r;
    int g;
    int b;

    r1 = (color1 >> 16) & 0xFF;
    g1 = (color1 >> 8) & 0xFF;
    b1 = color1 & 0xFF;
    r2 = (color2 >> 16) & 0xFF;
    g2 = (color2 >> 8) & 0xFF;
    b2 = color2 & 0xFF;
    r = r1 + t * (r2 - r1);
    g = g1 + t * (g2 - g1);
    b = b1 + t * (b2 - b1);
    return (r << 16) | (g << 8) | b;
}
