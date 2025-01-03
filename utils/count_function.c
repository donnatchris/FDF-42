/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:17:03 by christophed       #+#    #+#             */
/*   Updated: 2025/01/03 09:29:26 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/fdf.h"

// Count the number of columns in the first line of a file
int	count_columns(char *file)
{
	ft_printf("count_columns\n");
	int		fd;
	char	*line;
	char 	**tab;
	int		n_columns;
	
	n_columns = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Error opening file");
	line = get_next_line(fd);
	if (!line)
		close_fd_and_error(fd, "Error reading file");
	tab = ft_split(line, ' ');
	if (!tab)
	{
		free(line);
		close_fd_and_error(fd, "Error splitting line");
	}
	while (tab[n_columns])
		n_columns++;
	free_str_tab(tab);
	free (line);
	close(fd);
	return (n_columns);
}

// Count the number of lines in a file
int	count_lines(char *file)
{
	ft_printf("count_lines\n");
	int		fd;
	int		n_lines;

	n_lines = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Error opening file");
	while (get_next_line(fd))
		n_lines++;
	close(fd);
	return (n_lines);
}