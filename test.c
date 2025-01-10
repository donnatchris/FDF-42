/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:35:06 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/10 12:01:00 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compil with:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -lX11 -lXext -lm
// avec la libft:
// gcc -o progtest test.c -Lmlx -Imlx -lmlx -Llibft -Ilibft -lft -lX11 -lXext -lm

#include "mlx/mlx.h"
#include <stdarg.h>
#include "../libft/includes/libft.h"

typedef struct s_win
{
	void	*mlx_ptr;
	void 	*win_ptr;
}			t_win;

typedef struct point
{
	int		x;
	int		y;
	t_win	*win;
}			t_point;

// Function to free multiple pointers
int	multiple_free(int count, ...)
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

// Function to deal with key events
int	deal_key(int key, t_point *point)
{
	int	x;
	int	y;
	
	ft_printf("Touche pressee: %d\n", key);
	x = point->x;
	y = point->y;

	// dessine un pixel
	mlx_pixel_put(point->win->mlx_ptr, point->win->win_ptr, x, y, 0xFFFFFF);

	// incremente pour le prochain pixel
	point->x += 10;
	point->y += 10;

	return (0);
}

// Function to initialise the window
t_win	*init_win(void)
{
	t_win	*win;

	win = malloc(sizeof(t_win));
	if (!win)
		return (NULL);
	
	// initialise la connexion avec le serveur X
	win->mlx_ptr = mlx_init();

	// cree une fenetre
	win->win_ptr = mlx_new_window(win->mlx_ptr, 500, 500, "Hello World!");
	return (win);
}



int	main(void)
{
	t_win	*win;
	t_point	*point;

	win = init_win();
	if (!win)
		return (1);
	point = malloc(sizeof(t_point));
	if (!point)
		return (multiple_free(1, win), 1);

	// gere les evenements
	mlx_key_hook(win->mlx_ptr, deal_key, point);

	// demarre la boucle d'evenements
	mlx_loop(win->mlx_ptr);

	return (0);
}
