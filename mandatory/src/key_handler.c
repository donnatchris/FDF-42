/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:31:09 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/24 10:13:13 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to handle keys on Linux
int	deal_key(int key, t_fdf *fdf)
{
	if (key == 65307)
		free_and_exit(fdf);
	if (key == 65451 || key == 65453 || key == 65365 || key == 65366)
		zoom_and_depth(key, fdf);
	if (key == 65361 || key == 65363 || key == 65362 || key == 65364)
		translate(key, fdf);
	if (key == 97 || key == 115 || key == 113 || key == 119 \
		|| key == 122 || key == 120)
		rotate(key, fdf);
	if (key == 105 || key == 112 || key == 32)
		change_view(key, fdf);
	return (0);
}

// Function to change view or launch color animation
void	change_view(int key, t_fdf *fdf)
{
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
			fdf->anim_on = 1;
	}
}

// Function to change zoom or z depth
void	zoom_and_depth(int key, t_fdf *fdf)
{
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
}

// Function to rotate the view
void	rotate(int key, t_fdf *fdf)
{
	if (key == 97)
		fdf->ox += 0.1;
	if (key == 115)
		fdf->ox -= 0.1;
	if (key == 113)
		fdf->oy += 0.1;
	if (key == 119)
		fdf->oy -= 0.1;
	if (key == 122)
		fdf->oz += 0.1;
	if (key == 120)
		fdf->oz -= 0.1;
}

// Function to translate the view
void	translate(int key, t_fdf *fdf)
{
	if (key == 65361)
		fdf->originx -= 10;
	if (key == 65363)
		fdf->originx += 10;
	if (key == 65362)
		fdf->originy -= 10;
	if (key == 65364)
		fdf->originy += 10;
}
