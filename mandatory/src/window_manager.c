/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:09:47 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/15 08:30:30 by chdonnat         ###   ########.fr       */
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

int	free_and_exit(t_fdf *fdf)
{
	free_fdf(fdf);
	exit (1);
}

void	init_fdf(t_fdf *fdf, t_point **point)
{
	ft_printf("init_fdf\n");
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		free_and_exit(fdf);
	fdf->win_width = 1800;
	fdf->win_height = 1000;
	fdf->point = point;
	ft_printf("before find max\n");
	fdf->x_max = find_x_max(fdf);
	fdf->y_max = find_y_max(fdf);
	ft_printf("after find max\n");
    fdf->zoom = 30;
    fdf->depth = 0;
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

void	print_menu(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 30, DARK_BLUE, "Zoom = + / -");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 50, DARK_BLUE, "Depth = Page up / Page down");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 70, DARK_BLUE, "Exit = ESC");
}
