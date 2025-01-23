/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:35:06 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/23 14:56:03 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int ac, char **av)
{
	t_point	**point;
	t_fdf	*fdf;
	
	errno = 0;
	if (ac != 2)
		error("Wrong number of arguments");
	point = read_and_extract(av[1]);
	fdf = malloc_fdf();
	if (!fdf)
		return (ft_printf("memory allocation failed"),1);
	init_fdf(fdf, point);
	project_map(fdf);
	draw_lines(fdf);
	print_menu(fdf);
	mlx_hook(fdf->win_ptr, 2, 1L << 0, deal_key, fdf);
	mlx_hook(fdf->win_ptr, 17, 0L, free_and_exit, fdf);
	mlx_loop_hook(fdf->mlx_ptr, render, fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}

