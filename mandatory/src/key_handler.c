/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:31:09 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/23 10:07:14 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to handle keys on Linux
int	deal_key(int key, t_fdf *fdf)
{
	ft_printf("key pressed : %d\n", key);
	
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
	{
		if (fdf->depth < 1)
			fdf->depth += 0.1;
	}
	if (key == 65366)
	{
		if (fdf->depth > -1)
			fdf->depth -= 0.1;
	}
	if (key == 65361)
		fdf->originX -= 10;
	if (key == 65363)
		fdf->originX += 10;
	if (key == 65362)
		fdf->originY -= 10;
	if (key == 65364)
		fdf->originY += 10;
	if (key == 97)
		fdf->Ox += 0.1;
	if (key == 115)
		fdf->Ox -= 0.1;
	if (key == 100)
		fdf->Oy += 0.1;
	if (key == 102)
		fdf->Oy -= 0.1;
	if (key == 105)
		initialize_isometric_view(fdf);
	if (key == 112)
		initialize_perspective_view(fdf);
	if (key == 32)
	{
		if (fdf->anim_on)
		{
			fdf->anim_on = 0;
			initialize_colors(fdf);
		}
		else if (!fdf->anim_on)
		{
			fdf->anim_on = 1;
		}
	}
	clear_image(fdf);
	return (0);
}
