/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:43:07 by christophed       #+#    #+#             */
/*   Updated: 2025/01/23 11:56:02 by chdonnat         ###   ########.fr       */
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
    if (fdf->iso_on)
    {
        mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 30, fdf->menu_color, "--------- ISOMETRIC  VIEW ---------");
        mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 80, fdf->menu_color, "Press P to switch to perspective view");
        mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 110, fdf->menu_color, "Press I to reset view");
    }
    else
    {
        mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 30, fdf->menu_color, "--------- PERPECTIVE VIEW ---------");
        mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 80, fdf->menu_color, "Press I to switch to isometric view");
        mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 110, fdf->menu_color, "Press P to reset view");
    }
    mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 200, fdf->menu_color, "---------      KEYS       ---------");
    mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 250, fdf->menu_color, "ZOOM: ........ + / -");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 280, fdf->menu_color, "DEPTH: ....... Page up / Page down");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 310, fdf->menu_color, "MOVE: ........ Arrows");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 340, fdf->menu_color, "ROTATE: ...... a / s / d / f");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 370, fdf->menu_color, "EXIT: ........ esc");
    if (fdf->anim_on)
        animate_menu(fdf);
}

void    animate_menu(t_fdf *fdf)
{
	int			color1;
	int			color2;
	int			color3;

	color1 = fdf->up_color;
	color2 = fdf->zero_color;
	color3 = fdf->low_color;
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 460, color1, "---------       DISCO        --------");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 490, color2, "---------       MODE         --------");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 520, color3, "---------     ACTIVATED      --------");
}

