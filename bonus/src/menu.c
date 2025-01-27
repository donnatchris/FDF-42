/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:27:09 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/27 11:31:57 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to print the menu on screen
void	print_menu(t_fdf *fdf)
{
	if (fdf->iso_on)
		menu_iso(fdf);
	else
		menu_perspective(fdf);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 200, fdf->menu_color, \
		"---------   KEYS    ---------");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 250, fdf->menu_color, \
		"ZOOM: ..... + / -");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 280, fdf->menu_color, \
		"DEPTH: .... Page up / Page down");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 310, fdf->menu_color, \
		"MOVE: ..... Arrows");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 340, fdf->menu_color, \
		"ROTATE: ... a / s / d / f");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 370, fdf->menu_color, \
		"DISCO: .. space");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 400, fdf->menu_color, \
		"EXIT: ..... esc");
	if (fdf->anim_on)
		animate_menu(fdf);
}

void	menu_iso(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 30, fdf->menu_color, \
		"------ ISOMETRIC  VIEW ------");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 80, fdf->menu_color, \
		"switch to perspective view: P");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 110, fdf->menu_color, \
		"reset view: I");
}

void	menu_perspective(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 30, fdf->menu_color, \
		"--------- PERPECTIVE VIEW ---------");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 80, fdf->menu_color, \
		"switch to isometric view: I");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 110, fdf->menu_color, \
		"reset view: P");
}

void	animate_menu(t_fdf *fdf)
{
	int			color1;
	int			color2;
	int			color3;

	color1 = fdf->up_color;
	color2 = fdf->zero_color;
	color3 = fdf->low_color;
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 460, color1, \
		"---------    DISCO     --------");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 490, color2, \
		"---------    MODE      --------");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 520, color3, \
		"---------  ACTIVATED   --------");
}
