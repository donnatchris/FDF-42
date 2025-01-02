/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:42:47 by christophed       #+#    #+#             */
/*   Updated: 2025/01/02 18:42:50 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/fdf.h"

// Print an error message and exit the program
int		error(char *message)
{
	if (errno)
		perror(message);
	else
		ft_printf("%s\n", message);
	exit (1);
}

// Close a file descriptor and print an error message before exiting the program
void	close_fd_and_error(int fd, char *message)
{
	close(fd);
	error(message);
}

// Free the memory allocated for a table of t_points
// and close a file descriptor before exiting the program
void	free_close_fd_and_error(int fd, t_point **tab, char *message)
{
	free_points_tab(tab);
	close_fd_and_error(fd, message);
}
