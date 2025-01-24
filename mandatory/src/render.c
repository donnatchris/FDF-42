/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:43:07 by christophed       #+#    #+#             */
/*   Updated: 2025/01/24 10:27:55 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to generate the image
int	render(t_fdf *fdf)
{
	clear_image(fdf);
	fdf->sinox = sinf(fdf->ox);
	fdf->cosox = cosf(fdf->ox);
	fdf->sinoy = sinf(fdf->oy);
	fdf->cosoy = cosf(fdf->oy);
	fdf->sinoz = sinf(fdf->oz);
	fdf->cosoz = cosf(fdf->oz);
	animation(fdf);
	project_map(fdf);
	draw_lines(fdf);
	print_menu(fdf);
	return (0);
}

// Function to clear the image
void	clear_image(t_fdf *fdf)
{
	int	x;
	int	y;

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
void	project_map(t_fdf *fdf)
{
	int	i;

	fill_color(fdf);
	i = 0;
	while (fdf->point[i])
	{
		if (fdf->iso_on)
			project_isometric_point(fdf->point[i], fdf);
		else
			project_perspective_point(fdf->point[i], fdf);
		i++;
	}
}
