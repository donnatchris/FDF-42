/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_extract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:21:10 by christophed       #+#    #+#             */
/*   Updated: 2025/01/02 19:32:17 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/fdf.h"

void	read_and_extract(char *file)
{
	t_point	**src;
	int		n_columns;
	int		n_lines;

	n_columns = count_columns(file);
	n_lines = count_lines(file);
	if (n_columns == 0 || n_lines == 0)
		error("Invalid file");
	src = create_point_tab(file, n_columns, n_lines);
}

// Create a table of points from a file
t_point	**create_point_tab(char *file, int column_max, int line_max)
{
	t_point	**point_tab;
	int		fd;
	char	*line;
	int		n_line;

	point_tab = malloc(sizeof(t_point *) * (line_max * column_max));
	if (!point_tab)
		error("Error allocating memory");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Error opening file");
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
	return (point_tab);
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
	point->x = x;
	point->y = y;
	point->z = ft_atoi(str);
}

// Check if the string is a valid z coordinate (must be an integer)
int		input_is_valid(char *str)
{
	int		i;
	long	nbr;

	i = 0;
	if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	nbr = ft_atoi_long(str);
	if (nbr > 2147483647 || nbr < -2147483648)
		return (0);
	return (1);
}
