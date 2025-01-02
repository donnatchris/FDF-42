/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:34:30 by christophed       #+#    #+#             */
/*   Updated: 2025/01/02 19:29:01 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/fdf.h"

int	main(int ac, char **av)
{
	errno = 0;
	if (ac != 2)
		error("Wrong number of arguments");
	read_and_extract(av[1]);

	return (0);
}