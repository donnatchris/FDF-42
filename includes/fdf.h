/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:02:09 by christophed       #+#    #+#             */
/*   Updated: 2025/01/03 10:35:41 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// Libraries
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>

// Structure
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

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

// BONUS DIRECTORY

#endif
