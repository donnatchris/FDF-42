/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:30:44 by christophed       #+#    #+#             */
/*   Updated: 2025/01/23 02:00:38 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to print a table of points
void	print_point_tab(t_point **tab)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (tab[i])
	{
		if (tab[i]->y != y)
		{
			ft_printf("\n");
			y = tab[i]->y;
		}
		ft_printf("%d ",tab[i]->z);
		i++;
	}
	ft_printf("\n");
}

// Function to free multiple pointers
// void	multiple_free(int count, ...)
// {
// 	va_list	args;
// 	void	*ptr;
// 	int		i;

// 	va_start(args, count);
// 	i = 0;
// 	while (i < count)
// 	{
// 		ptr = va_arg(args, void *);
// 		free(ptr);
// 		i++;
// 	}
// 	va_end(args);
// }

