/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:42:47 by christophed       #+#    #+#             */
/*   Updated: 2025/01/22 11:12:38 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Print an error message and exit the program
int		error(char *message)
{
	ft_printf("Error\n");
	if (errno)
		perror(message);
	else
		ft_printf("%s\n", message);
	exit (1);
}

// Close a file descriptor and print an error message before exiting the program
void	close_fd_and_error(int fd, char *message)
{
	if (fd >= 0)
		close(fd);
	error(message);
}

// Free the memory allocated for a table of t_points
// and close a file descriptor before exiting the program
void	free_close_fd_and_error(int fd, t_point **tab, char *message)
{
	if (tab)
		free_points_tab(tab);
	close_fd_and_error(fd, message);
}

// Check if the string is a valid z coordinate (must be an integer)
int		input_is_valid(char *str)
{
	(void) str;
// 	ft_printf("input_is_valid\n");
// 	int		i;
// 	long	nbr;

// 	i = 0;
// 	if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 		i++;
// 	while (str[i])
// 	{
// 		if (!ft_isdigit(str[i]) && (str[i] != '\n'))
// 			return (0);
// 		i++;
// 	}
// 	nbr = ft_atoi_long(str);
// 	if (nbr > 2147483647 || nbr < -2147483648)
// 		return (0);
 	return (1);
}