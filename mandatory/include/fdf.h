/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:02:09 by christophed       #+#    #+#             */
/*   Updated: 2025/01/13 13:34:12 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// Libraries
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
#include <stdarg.h>
#include "../../libft/includes/libft.h"
# ifdef __APPLE__
#  include "../../mlx_mac/mlx.h"
# endif
# ifdef __linux__
#  include "../../mlx_linux/mlx.h"
# endif

// Constants
// Colors
// Red Colors
#define RED 0xFF0000            // Red (Pure Red)
#define DARK_RED 0x8B0000       // Dark Red
#define LIGHT_RED 0xFF6347      // Tomato (Light Red)
// Green Colors
#define GREEN 0x00FF00          // Green (Pure Green)
#define DARK_GREEN 0x006400     // Dark Green
#define LIGHT_GREEN 0x90EE90    // Light Green
// Blue Colors
#define BLUE 0x0000FF           // Blue (Pure Blue)
#define DARK_BLUE 0x00008B      // Dark Blue
#define LIGHT_BLUE 0xADD8E6     // Light Blue
// Yellow Colors
#define YELLOW 0xFFFF00         // Yellow (Pure Yellow)
#define GOLD 0xFFD700           // Gold
#define LIGHT_YELLOW 0xFFFFE0   // Light Yellow
// Cyan Colors
#define CYAN 0x00FFFF           // Cyan
#define DARK_CYAN 0x008B8B      // Dark Cyan
#define LIGHT_CYAN 0xE0FFFF     // Light Cyan
// Magenta Colors
#define MAGENTA 0xFF00FF        // Magenta
#define DARK_MAGENTA 0x8B008B   // Dark Magenta
#define LIGHT_MAGENTA 0xDDA0DD  // Plum (Light Magenta)
// White and Black
#define WHITE 0xFFFFFF          // White
#define BLACK 0x000000          // Black
#define GREY 0x808080           // Grey
#define DARK_GREY 0xA9A9A9      // Dark Grey
#define LIGHT_GREY 0xD3D3D3     // Light Grey
// Other Colors
#define ORANGE 0xFFA500         // Orange
#define PINK 0xFFC0CB           // Pink
#define PURPLE 0x800080         // Purple
#define BROWN 0xA52A2A          // Brown
#define BEIGE 0xF5F5DC          // Beige
#define LIME 0x00FF00           // Lime
#define INDIGO 0x4B0082         // Indigo
#define TURQUOISE 0x40E0D0      // Turquoise
#define CORAL 0xFF7F50          // Coral

// Structure
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

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

//SRC DIRECTORY
// error_manager.c
// print error messages, free allocated memory, close fd and exit the program
int		error(char *message);
void	close_fd_and_error(int fd, char *message);
void	free_close_fd_and_error(int fd, t_point **tab, char *message);
// read_and_extract.c
// read the file and create a table of points
void	read_and_extract(char *file);
void	create_point_tab(t_point **point_tab, char *file, int column_max, int line_max);
void	fill_src(int fd, t_point **src, char *line, int n_line, int column_max);
void	fill_coordonates(t_point *point, int x, int y, char *str);
int		input_is_valid(char *str);
t_point	**allocate_point_memory(t_point **src, int size);
// points.c
// creates three and two dimensional point tables
// limits.c
// defines which point should connect to another point
// draw.c
// draws with formulas and functions
// hooks.c
// interacts with the mouse and keyboard

// UTILS DIRECTORY
// free_functions.c
// free memory allocated for tables
void	free_points_tab(t_point **tab);
void	free_str_tab(char **tab);
// count_functions.c
// counts the number of columns and lines in a file
int	count_columns(char *file);
int	count_lines(char *file);
// ft_atoi_long.c
// converts a string to a long integer
long	ft_atoi_long(const char *nptr);
// test_functions.c
// tests functions to be removed before the final version
void	print_point_tab(t_point **tab);

int	free_and_exit(t_fdf *fdf);
void	my_mlx_pixel_put(t_fdf	*fdf, int x, int y, int color);


// linux or MacOs functions
int		deal_key(int key, t_fdf *fdf);
void	free_fdf(t_fdf *fdf);

// BONUS DIRECTORY

#endif
