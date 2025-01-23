/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:25:08 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/23 17:01:41 by chdonnat         ###   ########.fr       */
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
	while (j <= fdf->x_max * fdf->y_max)
	{
		bres.x0 = (int)fdf->point[start + i]->x_out;
		bres.y0 = (int)fdf->point[start + i]->y_out;
		bres.x1 = (int)fdf->point[start + j]->x_out;
		bres.y1 = (int)fdf->point[start + j]->y_out;
		color0 = fdf->point[start + i]->color;
		color1 = fdf->point[start + j]->color;
		bresenham(fdf, &bres, color0, color1);
		j = i;
		i = i + fdf->x_max + 1;
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

// Function to draw all the lines
void	draw_lines(t_fdf *fdf)
{
	int	start;
	int	line;
	int	column;

	start = 0;
	line = 0;
	while (line <= fdf->y_max)
	{
		draw_horizontal_line(fdf, start);
		start += fdf->x_max + 1;
		line++;
	}
	start = 0;
	column = 0;
	while (column <= fdf->x_max)
	{
		draw_vertical_line(fdf, column);
		start += fdf->y_max + 1;
		column++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}

// Function to draw a line between two points
void	bresenham(t_fdf *fdf, t_bres *bres, int color0, int color1)
{
	bres->dx = abs(bres->x1 - bres->x0);
	bres->dy = abs(bres->y1 - bres->y0);
	bres->sx = compare(bres->x0, bres->x1);
	bres->sy = compare(bres->y0, bres->y1);
	bres->err = bres->dx - bres->dy;
	bres->total_dist = sqrt((bres->dx * bres->dx) + (bres->dy * bres->dy));
	bres->current_dist = 0.0;
	while (bres->x0 != bres->x1 || bres->y0 != bres->y1)
	{
		bres->color = interpolate_color(color1, color0, bres->current_dist / bres->total_dist);
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
		bres->current_dist = sqrt((bres->x0 - bres->x1) * (bres->x0 - bres->x1) + (bres->y0 - bres->y1) * (bres->y0 - bres->y1));
	}
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
