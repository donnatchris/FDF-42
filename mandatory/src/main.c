/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:35:06 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/18 17:31:32 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// bressenham

// LINUX compil with:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -lX11 -lXext -lm
// avec la libft:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -Llibft -Ilibft -lft -lX11 -lXext -lm

// MAC compil with:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -Llibft -Ilibft/includes -lft -L/opt/homebrew/opt/libx11/lib -I/opt/homebrew/opt/libx11/include -L/opt/homebrew/opt/libxext/lib -I/opt/homebrew/opt/libxext/include -lX11 -lXext -lm -framework OpenGL -framework AppKit

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
	project_isometric_map(fdf);
	// draw_points(fdf);
	draw_lines(fdf);
	print_menu(fdf);
	if (fdf->anim_on)
		animate_colors(fdf);
	mlx_hook(fdf->win_ptr, 2, 1L << 0, deal_key, fdf);
	mlx_hook(fdf->win_ptr, 17, 0L, free_and_exit, fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}

