/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:31:09 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/16 13:02:33 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

#ifdef __linux__

// Function to handle keys on Linux
int	deal_key(int key, t_fdf *fdf)
{
	ft_printf("key pressed : %d\n", key);
	
	clear_image(fdf);
	if (key == 65307)
		free_and_exit(fdf);
	if (key == 65451)
		fdf->zoom += 1;
	if (key == 65453)
	{
		if (fdf->zoom > 1)
			fdf->zoom -= 1;
	}
	if (key == 65365)
		fdf->depth += 0.1;
	if (key == 65366)
		fdf->depth -= 0.1;
	if (key == 65361)
		fdf->translation_x -= 10;
	if (key == 65363)
		fdf->translation_x += 10;
	if (key == 65362)
		fdf->translation_y -= 10;
	if (key == 65364)
		fdf->translation_y += 10;
	project_isometric_map(fdf);
	draw_lines(fdf);
	print_menu(fdf);
	return (0);
}


#endif
