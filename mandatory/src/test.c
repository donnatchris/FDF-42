/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:35:06 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/11 20:57:43 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// LINUX compil with:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -lX11 -lXext -lm
// avec la libft:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -Llibft -Ilibft -lft -lX11 -lXext -lm

// MAC compil with:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -Llibft -Ilibft/includes -lft -L/opt/homebrew/opt/libx11/lib -I/opt/homebrew/opt/libx11/include -L/opt/homebrew/opt/libxext/lib -I/opt/homebrew/opt/libxext/include -lX11 -lXext -lm -framework OpenGL -framework AppKit


// #include "../mlx_mac/mlx.h"
// #include <stdarg.h>
// #include "../../libft/includes/libft.h"

#include "../include/fdf.h"

typedef struct s_img
{
	void		*img_p;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_win
{
	void		*mlx_p;
	void 		*win_p;
}				t_win;

typedef struct s_pix
{
	int			x;
	int			y;
}				t_pix;

typedef struct s_gen
{
	t_img		*img;
	t_win		*win;
	t_pix		*pix;
	int			size_x;
	int			size_y;
}				t_gen;

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
void	free_gen(t_gen *gen)
{
	if (gen)
	{
		if (gen->win)
			free(gen->win);
		if (gen->img)
			free(gen->img);
		if (gen->pix)
			free(gen->pix);
		free (gen);
	}
}

// Fonction pour initialiser la fenetre et l'image
t_gen	*malloc_gen(void)
{
	t_gen	*gen;

	gen = (t_gen *)malloc(sizeof(t_gen));
	if (!gen)
		return (NULL);
	gen->win = (t_win *)malloc(sizeof(t_win));
	if (!gen->win)
		return (free(gen), NULL);
	gen->img = (t_img *)malloc(sizeof(t_img));
	if (!gen->img)
		return (multiple_free(2, gen->win, gen), NULL);
	gen->pix = (t_pix *)malloc(sizeof(t_pix));
	if (!gen->pix)
		return (multiple_free(3, gen->img, gen->win, gen), NULL);
	return (gen);
}

void	free_and_exit(t_gen *gen)
{
	free_gen(gen);
	exit (1);
}

void	init_gen(t_gen *gen)
{
	gen->win->mlx_p = mlx_init();
	if (!gen->win->mlx_p)
		free_and_exit(gen);
	gen->size_x = 500;
	gen->size_y = 500;
	gen->win->win_p = mlx_new_window(gen->win->mlx_p, gen->size_x, \
		gen->size_y, "O");
	if (!gen->win->win_p)
		free_and_exit(gen);
	gen->img->img_p = mlx_new_image(gen->win->mlx_p, gen->size_x, gen->size_y);
	if (!gen->img->img_p)
		free_and_exit(gen);
	gen->img->bpp = 24;
	gen->img->addr = mlx_get_data_addr(gen->img->img_p, &gen->img->bpp, \
		&gen->img->line_length, &gen->img->endian);
	if (!gen->img->addr)
		free_and_exit(gen);
}

void	my_mlx_pixel_put(t_gen	*gen, int x, int y, int color)
{
	char	*dst;

	dst = gen->img->addr + (y * gen->img->line_length + x * (gen->img->bpp / 8));
	*(unsigned int *)dst = color;
}

#ifdef __APPLE__
int	deal_key(int key, t_gen *gen)
{
	static int x = 10;
	static int y = 10;

	ft_printf("key: %d\n", key);

	// Touche ESC
	if (key == 53)
	{
		mlx_destroy_window(gen->win->mlx_p, gen->win->win_p);
		free_and_exit(gen);
	}
	else if (key == 35)
    {
		mlx_string_put(gen->win->mlx_p, gen->win->win_p, 20, 20, 0x00FF00, "Hello World!");
        // Dessiner un pixel à la position x, y
        my_mlx_pixel_put(gen, x, y, 0x00FF00); // Vert
        // Afficher l'image dans la fenêtre
        mlx_put_image_to_window(gen->win->mlx_p, gen->win->win_p, gen->img->img_p, 0, 0);
        // Déplacer les coordonnées pour le prochain pixel
        x += 1;
        y += 1;
    }
	mlx_put_image_to_window(gen->win->mlx_p, gen->win->win_p, gen->img->img_p, 0, 0);
	// Déplacer les coordonnées pour le prochain pixel

	return (0);
}
#endif

#ifdef __linux__
int	deal_key(int key, t_gen *gen)
{
	static int x = 10;
	static int y = 10;

	if (key == 65307)
	{
		mlx_destroy_window(gen->win->mlx_p, gen->win->win_p);
		free_and_exit(gen);
	}
	// Dessiner un pixel à la position x, y
	my_mlx_pixel_put(gen, x, y, 0x00FF00); // Vert
	// Afficher l'image dans la fenêtre
	mlx_put_image_to_window(gen->win->mlx_p, gen->win->win_p, gen->img->img_p, 0, 0);
	// Déplacer les coordonnées pour le prochain pixel
	x += 1;
	y += 1;

	return (0);
}
#endif

int	render_next_frame(t_gen *gen)
{
    // Mettre à jour la fenêtre régulièrement
    mlx_put_image_to_window(gen->win->mlx_p, gen->win->win_p, gen->img->img_p, 0, 0);
    return (0);
}

int	main(void)
{
	t_gen	*gen;

	gen = malloc_gen();
	if (!gen)
		return (ft_printf("MEMORY ALLOCATION ERROR"),1);
	init_gen(gen);
	mlx_key_hook(gen->win->win_p, deal_key, gen);
	mlx_loop_hook(gen->win->mlx_p, render_next_frame, gen); // Mettre à jour la fenêtre régulièrement
	mlx_loop(gen->win->mlx_p);
}

