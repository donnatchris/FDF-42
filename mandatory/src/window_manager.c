/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:09:47 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/23 00:19:02 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


// Fonction pour initialiser la fenetre et l'image
t_fdf	*malloc_fdf(void)
{
	t_fdf	*fdf;

	fdf = NULL;
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	return (fdf);
}



void	init_fdf(t_fdf *fdf, t_point **point)
{
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		free_and_exit(fdf);
	fdf->point = point;
	init_values(fdf);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_width, \
		fdf->win_height, "FdF");
	if (!fdf->win_ptr)
		free_and_exit(fdf);
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->win_width, fdf->win_height);
	if (!fdf->img_ptr)
		free_and_exit(fdf);
	fdf->bpp = 24;
	fdf->addr = mlx_get_data_addr(fdf->img_ptr, &fdf->bpp, &fdf->line_length, &fdf->endian);
	if (!fdf->addr)
		free_and_exit(fdf);
}

// Function to initialize values
void	init_values(t_fdf *fdf)
{
	fdf->anim_on = 0;
	fdf->win_width = 1800;
	fdf->win_height = 1000;
	fdf->originX = (fdf->win_width / 2);
	fdf->originY = (fdf->win_height / 2);
	fdf->x_max = find_x_max(fdf);
	fdf->y_max = find_y_max(fdf);
	fdf->z_max = find_z_max(fdf);
	calculate_center(fdf);
	center(fdf);
    fdf->factor = 30;
    fdf->depth = 0.1;
	fdf->Ox = -0.0764;
	fdf->Oy = 0.2854;
	fdf->Oz = 0;
	fdf->back_color = BLACK;
	fdf->zero_color = WHITE;
	fdf->up_color = DARK_GREEN;
	fdf->low_color = PURPLE;
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

// Function to find central points
void	calculate_center(t_fdf *fdf)
{
	int	n_points;
	int	i;

    n_points = fdf->x_max * fdf->y_max;
	fdf->x_mid = 0;
	fdf->y_mid = 0;
	fdf->z_mid = 0;
	i = 0;
	while (i < n_points)
	{
		fdf->x_mid += fdf->point[i]->x;
		fdf->y_mid += fdf->point[i]->y;
		fdf->z_mid += fdf->point[i]->z;
		i++;
	}
	fdf->x_mid = fdf->x_mid / n_points;
	fdf->y_mid = fdf->y_mid / n_points;
	fdf->z_mid = fdf->z_mid / n_points;
}

// Apply central decalage
void	center(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (fdf->point[i])
	{
		fdf->point[i]->x = fdf->point[i]->x - fdf->x_mid;
		fdf->point[i]->y = fdf->point[i]->y - fdf->y_mid;
		i++;
	}
}
