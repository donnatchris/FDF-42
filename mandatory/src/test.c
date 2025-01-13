/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:35:06 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/13 13:21:02 by chdonnat         ###   ########.fr       */
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



// Function to free multiple pointers
void	multiple_free(int count, ...)
{
	va_list	args;
	void	*ptr;
	int		i;

	va_start(args, count);
	i = 0;
	while (i < count)
	{
		ptr = va_arg(args, void *);
		free(ptr);
		i++;
	}
	va_end(args);
}

// Fonction pour initialiser la fenetre et l'image
t_fdf	*malloc_fdf(void)
{
	t_fdf	*fdf;

	fdf = NULL;
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	return (fdf);
}

int	free_and_exit(t_fdf *fdf)
{
	free_fdf(fdf);
	exit (1);
}

void	init_fdf(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		free_and_exit(fdf);
	fdf->win_width = 1000;
	fdf->win_height = 500;
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_width, \
		fdf->win_height, "FdF");
	if (!fdf->win_ptr)
		free_and_exit(fdf);
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->win_width, fdf->win_height);
	if (!fdf->img_ptr)
		free_and_exit(fdf);
	fdf->bpp = 24;
	fdf->addr = mlx_get_data_addr(fdf->img_ptr, &fdf->bpp, &fdf->line_length, &fdf->endian);
	if (!fdf->addr)
		free_and_exit(fdf);
}

void	my_mlx_pixel_put(t_fdf	*fdf, int x, int y, int color)
{
	char	*dst;

    if (x >= 0 && x < fdf->win_width && y >= 0 && y < fdf->win_height)
	{
        dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
        *(unsigned int *)dst = color;
    }
}

int	main(void)
{
	t_fdf	*fdf;

	fdf = malloc_fdf();
	if (!fdf)
		return (ft_printf("memory allocation failed"),1);
	init_fdf(fdf);
	mlx_hook(fdf->win_ptr, 2, 1L << 0, deal_key, fdf);
	mlx_hook(fdf->win_ptr, 17, 0L, free_and_exit, fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}

