/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:25:08 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/16 11:32:20 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to draw a vertical line
void	draw_vertical_line(t_fdf *fdf, int start)
{
	// ft_printf("draw_horizontal_line\n");
	int x0;
	int x1;
	int y0;
	int y1;
	int i;
	int j;
    int color;

    i = 0;
    j = fdf->x_max + 1;
    while (j <= fdf->x_max *fdf->y_max)
    {
        x0 = (int)fdf->point[start + i]->x_out;
        y0 = (int)fdf->point[start + i]->y_out;
        x1 = (int)fdf->point[start + j]->x_out;
        y1 = (int)fdf->point[start + j]->y_out;
        if (fdf->point[start + i]->z > fdf->point[start + j]->z)
            color = fdf->point[start + i]->color;
        else
            color = fdf->point[start + j]->color;
        bresenham(fdf, x0, y0, x1, y1, color);
		j = i;
        i = i + fdf->x_max + 1;
    }
}

// Function to draw a horizontal line
void	draw_horizontal_line(t_fdf *fdf, int start)
{
	// ft_printf("draw_horizontal_line\n");
	int x0;
	int x1;
	int y0;
	int y1;
	int i;
	int j;
    int color;

    i = 0;
    j = 1;
    while (j <= fdf->x_max)
    {
        x0 = (int)fdf->point[start + i]->x_out;
        y0 = (int)fdf->point[start + i]->y_out;
        x1 = (int)fdf->point[start + j]->x_out;
        y1 = (int)fdf->point[start + j]->y_out;
        if (fdf->point[start + i]->z > fdf->point[start + j]->z)
            color = fdf->point[start + i]->color;
        else
            color = fdf->point[start + j]->color;
        bresenham(fdf, x0, y0, x1, y1, color);
        i++;
        j++;
    }
}

// Function to draw all the lines
void	draw_lines(t_fdf *fdf)
{
    // ft_printf("draw_lines\n");
    int start;
	int line;
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
void bresenham(t_fdf *fdf, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1; // Direction en x
    int sy = (y0 < y1) ? 1 : -1; // Direction en y
    int err = dx - dy;           // Erreur initiale

    while (1)
    {
        put_pixel_to_image(fdf, x0, y0, color); // Dessiner le pixel
        if (x0 == x1 && y0 == y1)             // Si on atteint la fin de la ligne
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
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

// Function to draw points in the image
// void draw_points(t_fdf *fdf)
// {
//     ft_printf("draw_points\n");
//     int x;
//     int y;
//     int i;

//     i = 0;
//     while (fdf->point[i])
//     {
//         x = (int)fdf->point[i]->x_out;
//         y = (int)fdf->point[i]->y_out;
//         put_pixel_to_image(fdf, x, y, fdf->point[i]->color);
//         i++;
//     }
//     mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
// }

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
            put_pixel_to_image(fdf, x, y, BLACK);
            x++;
        }
        y++;
    }
}

