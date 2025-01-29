/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:25:08 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/29 08:26:23 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to draw a vertical line
void	draw_vertical_line(t_fdf *fdf, int start)
{
	t_bres	bres;
	int		i;
	int		j;
	int		color0;
	int		color1;

	i = 0;
	j = fdf->x_max + 1;
	while (j < (fdf->x_max + 1) * (fdf->y_max + 1))
	{
		if (!fdf->point[start + i] || !fdf->point[start + j])
			return ;
		bres.x0 = (int)fdf->point[start + i]->x_out;
		bres.y0 = (int)fdf->point[start + i]->y_out;
		bres.x1 = (int)fdf->point[start + j]->x_out;
		bres.y1 = (int)fdf->point[start + j]->y_out;
		color0 = fdf->point[start + i]->color;
		color1 = fdf->point[start + j]->color;
		bresenham(fdf, &bres, color0, color1);
		i = j;
		j = j + fdf->x_max + 1;
	}
}

// Function to draw a horizontal line
void	draw_horizontal_line(t_fdf *fdf, int start)
{
	t_bres	bres;
	int		i;
	int		j;
	int		color0;
	int		color1;

	i = 0;
	j = 1;
	while (j <= fdf->x_max)
	{
		if (!fdf->point[start + i] || !fdf->point[start + j])
			return ;
		bres.x0 = (int)fdf->point[start + i]->x_out;
		bres.y0 = (int)fdf->point[start + i]->y_out;
		bres.x1 = (int)fdf->point[start + j]->x_out;
		bres.y1 = (int)fdf->point[start + j]->y_out;
		color0 = fdf->point[start + i]->color;
		color1 = fdf->point[start + j]->color;
		bresenham(fdf, &bres, color0, color1);
		i++;
		j++;
	}
}

// Function to draw a line between two points
void	bresenham(t_fdf *fdf, t_bres *bres, int color0, int color1)
{
	set_bres_values(bres);
	while (bres->x0 != bres->x1 || bres->y0 != bres->y1)
	{
		if (bres->total_dist != 0)
			bres->color = interpolate_color(color1, color0, \
				bres->current_dist / bres->total_dist);
		else
			bres->color = color0;
		put_pixel_to_image(fdf, bres->x0, bres->y0, bres->color);
		bres->e2 = 2 * bres->err;
		if (bres->e2 > -bres->dy)
		{
			bres->err -= bres->dy;
			bres->x0 += bres->sx;
		}
		if (bres->e2 < bres->dx)
		{
			bres->err += bres->dx;
			bres->y0 += bres->sy;
		}
		bres->current_dist = sqrt((bres->x0 - bres->x1) * (bres->x0 \
			- bres->x1) + (bres->y0 - bres->y1) * (bres->y0 - bres->y1));
	}
	put_pixel_to_image(fdf, bres->x1, bres->y1, color1);
}

// Function to draw a pixel in the image
void	put_pixel_to_image(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < fdf->win_width && y >= 0 && y < fdf->win_height)
	{
		dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

// Function to set bresheneim values
void	set_bres_values(t_bres *bres)
{
	bres->dx = abs(bres->x1 - bres->x0);
	bres->dy = abs(bres->y1 - bres->y0);
	bres->sx = compare(bres->x0, bres->x1);
	bres->sy = compare(bres->y0, bres->y1);
	bres->err = bres->dx - bres->dy;
	bres->total_dist = sqrt((bres->dx * bres->dx) + (bres->dy * bres->dy));
	bres->current_dist = 0.0;
	bres->current_dist = 0.0;
	bres->color = 0;
}
