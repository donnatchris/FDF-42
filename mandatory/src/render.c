/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:43:07 by christophed       #+#    #+#             */
/*   Updated: 2025/01/23 10:41:47 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to generate the image
int	render(t_fdf *fdf)
{
    fdf->sinOx = sin(fdf->Ox);
    fdf->cosOx = cos(fdf->Ox);
    fdf->sinOy = sin(fdf->Oy);
    fdf->cosOy = cos(fdf->Oy);
    fdf->sinOz = sin(fdf->Oz);
    fdf->cosOz = cos(fdf->Oz);
	animation(fdf);
	project_map(fdf);
	draw_lines(fdf);
	print_menu(fdf);
	return (0);
}

// Function to clear the image
void clear_image(t_fdf *fdf)
{
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
void    project_map(t_fdf *fdf)
{
    int i;
    
    fill_color(fdf);
    i = 0;
    while(fdf->point[i])
    {
        if (fdf->iso_on)
            project_isometric_point(fdf->point[i], fdf);
        else
            project_perspective_point(fdf->point[i], fdf);
        i++;
    }

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

