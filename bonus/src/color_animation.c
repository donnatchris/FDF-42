/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:37:41 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/23 16:53:42 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to animate colors
void	animation(t_fdf *fdf)
{
	static int	i = 0;
	static int	j = 0;

	if (!fdf->anim_on)
	{
		i = 0;
		j = 0;
		initialize_colors(fdf);
		return ;
	}
	if (j < 4)
	{
		if (i < 30)
			i++;
		else
			slow_animation(fdf, &i, &j);
	}
	else
	{
		if (i < 3)
			i++;
		else
			fast_animation(fdf, &i, &j);
	}
}

// Function to animate colors slowly
void	slow_animation(t_fdf *fdf, int *i, int *j)
{
	int	temp_color;

	temp_color = fdf->up_color;
	swap_colors(&fdf->up_color, &fdf->zero_color);
	swap_colors(&fdf->zero_color, &fdf->low_color);
	swap_colors(&fdf->low_color, &fdf->ghost_color);
	swap_colors(&fdf->ghost_color, &temp_color);
	*i = 0;
	(*j)++;
}

// Function to animate colors fast
void	fast_animation(t_fdf *fdf, int *i, int *j)
{
	int	temp_color;

	temp_color = fdf->up_color;
	swap_colors(&fdf->up_color, &fdf->zero_color);
	swap_colors(&fdf->zero_color, &fdf->low_color);
	swap_colors(&fdf->low_color, &fdf->ghost_color);
	swap_colors(&fdf->ghost_color, &temp_color);
	*i = 0;
	(*j)++;
	if (*j > 40)
		*j = 0;
}

// Function to swap 2 olors
void	swap_colors(int *color1, int *color2)
{
	int	temp;

	temp = *color1;
	*color1 = *color2;
	*color2 = temp;
}
