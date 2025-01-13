/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:31:09 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/13 13:35:07 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

#ifdef __linux__

// Function to handle keys on Linux
int	deal_key(int key, t_fdf *fdf)
{
	static int x = 10;
	static int y = 10;
	
	ft_printf("key pressed : %d\n", key);
	if (key == 65307)
		free_and_exit(fdf);
	
	my_mlx_pixel_put(fdf, x, y, PINK);
	x += 1;
	y += 1;
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	return (0);
}

// Function to free the memory allocated for the fdf structure on Linux
void	free_fdf(t_fdf *fdf)
{
	if (fdf)
	{
		if (fdf->img_ptr)
			mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
		if (fdf->win_ptr)
			mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		if (fdf->mlx_ptr)
			mlx_destroy_display(fdf->mlx_ptr);
		free(fdf->mlx_ptr);
		free(fdf);
	}
}

#endif
