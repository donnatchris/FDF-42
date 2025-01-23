/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_extract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:21:10 by christophed       #+#    #+#             */
/*   Updated: 2025/01/23 02:05:41 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_point	**read_and_extract(char *file)
{
	t_point	**src;
	int		n_columns;
	int		n_lines;

	n_columns = count_columns(file);
	n_lines = count_lines(file);
	if (n_columns == 0 || n_lines == 0)
		error("Invalid file");
	src = NULL;
	src = allocate_point_memory(src, (n_columns * n_lines));
	create_point_tab(src, file, n_columns, n_lines);
	return (src);
}

// Create a table of points from a file
void	create_point_tab(t_point **point_tab, char *file, int column_max, int line_max)
{
	int		fd;
	char	*line;
	int		n_line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		free_close_fd_and_error(fd, point_tab, "Error opening file");
	n_line = 0;
	while (n_line < line_max)
	{
		line = get_next_line(fd);
		if (!line)
			free_close_fd_and_error(fd, point_tab, "Error reading file");
		fill_src(fd, point_tab, line, n_line, column_max);
		free(line);
		n_line++;
	}
	close(fd);
}

// Fill a table of points with the values of a line
void	fill_src(int fd, t_point **src, char *line, int n_line, int column_max)
{
	char	**tab;
	int		n_column;
	int 	index;

	tab = ft_split(line, ' ');
	if (!tab)
		free_close_fd_and_error(fd, src, "Error splitting line");
	n_column = 0;
	while (tab[n_column])
	{
		if (!input_is_valid(tab[n_column]))
		{
			free_str_tab(tab);
			free_close_fd_and_error(fd, src, "Invalid file");
		}
		index = n_line * column_max + n_column;
		fill_coordonates(src[index], n_column, n_line, tab[n_column]);
		n_column++;
	}
	free_str_tab(tab);
	if (n_column != column_max)
		free_close_fd_and_error(fd, src, "Invalid file");
}

// Fill the coordinates of a point
void	fill_coordonates(t_point *point, int x, int y, char *str)
{
	if (!point)
    {
        ft_printf("Point is NULL\n");
        return;
    }
	point->x = x;
	point->y = y;
	point->z = ft_atoi(str);
}


// Allocate memory for a table of points
t_point	**allocate_point_memory(t_point **src, int size)
{
	int		i;
	
	src = (t_point **)malloc(sizeof(t_point *) * (size + 1));
	if (!src)
		error("Error allocating memory");
	i = 0;
	while (i < size)
	{
		src[i] = (t_point *)malloc(sizeof(t_point));
		if (!src[i])
		{
			while (i >= 0)
				free(src[i--]);
			free(src);
			error("Error allocating memory");
		}
		i++;
	}
	src[size] = NULL;
	return (src);
}
