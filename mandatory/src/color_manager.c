/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:14:10 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/16 11:47:38 by chdonnat         ###   ########.fr       */
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
int	color_manager(int z, t_fdf *fdf)
{
    double t;
    int color1;
    int color2;

    if (z <= 0)
        return (WHITE);
    else if (z >= fdf->altitude_max)
        return (DARK_RED);
    else if (z < fdf->altitude_max / 4)
    {
        color1 = WHITE;
        color2 = YELLOW;
    }
    else if (z < fdf->altitude_max / 2)
    {
        color1 = YELLOW;
        color2 = ORANGE;
    }
    else if (z < fdf->altitude_max * 3 / 4)
    {
        color1 = ORANGE;
        color2 = RED;
    }
    else
    {
        color1 = RED;
        color2 = DARK_RED;
    }
    t = (double)z / fdf->altitude_max;
    return interpolate_color(color1, color2, t);
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
