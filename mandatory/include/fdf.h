/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:02:09 by christophed       #+#    #+#             */
/*   Updated: 2025/01/23 09:30:37 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// Libraries
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <stdarg.h>
# include <math.h>
# include "colors.h"
# include "../../libft/includes/libft.h"
# ifdef __APPLE__
#  include "../../mlx_mac/mlx.h"
# endif
# ifdef __linux__
#  include "../../mlx_linux/mlx.h"
# endif

// Constants
# define COS_ANGLE 0.866
# define SIN_ANGLE 0.5

// Structure
typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	float	x_out;
	float	y_out;
	int		color;
}	t_point;

typedef struct s_bres
{
    int 	x0;
    int		y0;
    int		x1;
    int 	y1;
    int 	dx;
    int 	dy;
    int 	sx;
    int 	sy;
    int 	err;
    int 	e2;
    int		color;
	double	total_dist;
	double	current_dist;
}			t_bres;

typedef struct s_color
{
	int r1;
    int g1;
    int b1;
    int r2;
    int g2;
    int b2;
    int r;
    int g;
    int b;
}		t_color;

typedef struct	s_rotation
{
	float	x;
	float	y;
	float	z;
	float	temp_x;
	float	temp_y;
	float	temp_z;
	float	x_proj;
	float	y_proj;
}				t_rotation;

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
	int			originX;
	int			originY;
	float		x_max;
	float		y_max;
	float		z_max;
	float		x_mid;
	float		y_mid;
	float		z_mid;
	int			altitude_max;
	float		Ox;
	float		Oy;
	float		Oz;
	int			zoom;
	float		depth;
	float		distance;
	int			back_color;
	int			zero_color;
	int			up_color;
	int			low_color;
	int			ghost_color;
	int			iso_on;
	int			anim_on;
	t_point		**point;
}				t_fdf;

//SRC DIRECTORY
// error_manager.c
// print error messages, free allocated memory, close fd and exit the program
int		error(char *message);
void	close_fd_and_error(int fd, char *message);
void	free_close_fd_and_error(int fd, t_point **tab, char *message);
// read_and_extract.c
// read the file and create a table of points
t_point	**read_and_extract(char *file);
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
int		count_columns(char *file);
int		count_lines(char *file);
// ft_atoi_long.c
// converts a string to a long integer
long	ft_atoi_long(const char *nptr);
// test_functions.c
// tests functions to be removed before the final version
void	print_point_tab(t_point **tab);
int		free_and_exit(t_fdf *fdf);	
void	put_pixel_to_image(t_fdf	*fdf, int x, int y, int color);
t_fdf	*malloc_fdf(void);
int		free_and_exit(t_fdf *fdf);
void	init_fdf(t_fdf *fdf, t_point **point);
void	put_pixel_to_image(t_fdf *fdf, int x, int y, int color);
void 	project_isometric_point(t_point *point, t_fdf *fdf);
void    project_map(t_fdf *fdf);
// void 	draw_points(t_fdf *fdf);
void 	clear_image(t_fdf *fdf);
void bresenham(t_fdf *fdf, t_bres *bres, int color0, int color1);
void	draw_lines(t_fdf *fdf);
void	draw_horizontal_line(t_fdf *fdf, int start);
void	draw_vertical_line(t_fdf *fdf, int start);
int		find_x_max(t_fdf *fdf);
int		find_y_max(t_fdf *fdf);
int		find_z_max(t_fdf *fdf);
void	print_menu(t_fdf *fdf);
void	fill_color(t_fdf *fdf);
int		color_manager(float z, t_fdf *fdf);
int		interpolate_color(int color1, int color2, double t);
void	init_values(t_fdf *fdf);
int     compare(float n1, float n2);
void	swap_colors(int *color1, int *color2);
int		render(t_fdf *fdf);
void	animation(t_fdf *fdf);
void	slow_animation(t_fdf *fdf);
void	fast_animation(t_fdf *fdf);
void	initialize_colors(t_fdf *fdf);
void	calculate_center(t_fdf *fdf);
void	center(t_fdf *fdf);
void    project_perspective_point(t_point *point, t_fdf *fdf);


// linux or MacOs functions
void	free_fdf(t_fdf *fdf);
int		deal_key(int key, t_fdf *fdf);


// BONUS DIRECTORY

#endif
