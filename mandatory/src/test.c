/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:35:06 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/11 22:55:27 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// LINUX compil with:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -lX11 -lXext -lm
// avec la libft:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -Llibft -Ilibft -lft -lX11 -lXext -lm

// MAC compil with:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -Llibft -Ilibft/includes -lft -L/opt/homebrew/opt/libx11/lib -I/opt/homebrew/opt/libx11/include -L/opt/homebrew/opt/libxext/lib -I/opt/homebrew/opt/libxext/include -lX11 -lXext -lm -framework OpenGL -framework AppKit

#include "../include/fdf.h"
typedef struct s_fdf
{
	void		*mlx_ptr;
	void 		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			win_width;
	int			win_height;
}				t_fdf;

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

void	free_fdf(t_fdf *fdf)
{
	if (fdf)
	{
		// sur linux:
		// if (fdf->img_ptr)
		// 	mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
		// if (fdf->win_ptr)
		// 	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		// if (fdf->mlx_ptr)
		// 	mlx_destroy_display(fdf->mlx_ptr);
		free (fdf);
	}
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

void	free_and_exit(t_fdf *fdf)
{
	free_fdf(fdf);
	exit (1);
}

void	init_fdf(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		free_and_exit(fdf);
	fdf->win_width = 500;
	fdf->win_height = 500;
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_width, \
		fdf->win_height, "FdF");
	if (!fdf->win_ptr)
		free_and_exit(fdf);
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->win_width, fdf->win_height);
	if (!fdf->img_ptr)
		free_and_exit(fdf);
	fdf->bpp = 24;
	fdf->addr = mlx_get_data_addr(fdf->img_ptr, &fdf->bpp, \
		&fdf->line_length, &fdf->endian);
	if (!fdf->addr)
		free_and_exit(fdf);
}

void	my_mlx_pixel_put(t_fdf	*fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bpp / 8));
	*(unsigned int *)dst = color;
}

#ifdef __APPLE__
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
#endif

// #ifdef __linux__
// int	deal_key(int key, t_gen *gen)
// {
// 	static int x = 10;
// 	static int y = 10;

// 	if (key == 65307)
// 	{
// 		mlx_destroy_window(gen->win->mlx_p, gen->win->win_p);
// 		free_and_exit(gen);
// 	}
// 	// Dessiner un pixel à la position x, y
// 	my_mlx_pixel_put(gen, x, y, 0x00FF00); // Vert
// 	// Afficher l'image dans la fenêtre
// 	mlx_put_image_to_window(gen->win->mlx_p, gen->win->win_p, gen->img->img_p, 0, 0);
// 	// Déplacer les coordonnées pour le prochain pixel
// 	x += 1;
// 	y += 1;

// 	return (0);
// }
// #endif

int	render_next_frame(t_fdf *fdf)
{
    // Mettre à jour la fenêtre régulièrement
    mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
    return (0);
}

int	main(void)
{
	t_fdf	*fdf;

	fdf = malloc_fdf();
	if (!fdf)
		return (ft_printf("memory allocation failed"),1);
	init_fdf(fdf);
	mlx_key_hook(fdf->win_ptr, deal_key, fdf);
	mlx_loop_hook(fdf->mlx_ptr, render_next_frame, fdf); // Mettre à jour la fenêtre régulièrement
	mlx_loop(fdf->mlx_ptr);
	return (0);
}

