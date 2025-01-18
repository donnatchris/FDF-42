/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:31:09 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/18 17:28:20 by chdonnat         ###   ########.fr       */
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
		fdf->factor += 1;
	if (key == 65453)
	{
		if (fdf->factor > 1)
			fdf->factor -= 1;
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
	if (key == 114)
		rotate_iso_90(fdf);
	if (key == 97)
		fdf->Ox += 0.1;
	if (key == 115)
		fdf->Ox -= 0.1;
	if (key == 100)
		fdf->Oy += 0.1;
	if (key == 102)
		fdf->Oy -= 0.1;
	if (key == 105)
		{
			fdf->Ox = 0.7854;
			fdf->Oy = 0.6155;
		}
	if (key == 32)
	{
		fdf->anim_on = 1;
	}
	project_isometric_map(fdf);
	draw_lines(fdf);
	print_menu(fdf);
	return (0);
}

// Function to rotate the isometric view
void rotate_iso_90(t_fdf *fdf)
{
	ft_printf("rotate_iso_90\n");
	int	i;
	int	temp_x;

	i = 0;
	while (fdf->point[i])
	{
		temp_x = fdf->point[i]->x;
		fdf->point[i]->x = -fdf->point[i]->y;
		fdf->point[i]->y = temp_x;
		i++;
	}
}




#endif
