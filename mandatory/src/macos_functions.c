/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macos_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:31:34 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/13 13:22:47 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

#ifdef __APPLE__

// Function to handle keys on MacOS
int	deal_key(int key, t_fdf *fdf)
{
	static int x = 10;
	static int y = 10;

	ft_printf("key: %d\n", key);

	// Touche ESC
	if (key == 53)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		free_and_exit(fdf);
	}
	else if (key == 35)
    {
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 20, 0x00FF00, "Hello World!");
        // Dessiner un pixel à la position x, y
        my_mlx_pixel_put(fdf, x, y, 0x00FF00); // Vert
        // Afficher l'image dans la fenêtre
        x += 1;
        y += 1;
    }
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	// Déplacer les coordonnées pour le prochain pixel

	return (0);
}

// Function to free the memory allocated for the fdf structure on MacOs
void	free_fdf(t_fdf *fdf)
{
	if (fdf)
	{
		// a retirer sur mac?
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