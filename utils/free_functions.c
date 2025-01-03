/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:12:34 by christophed       #+#    #+#             */
/*   Updated: 2025/01/03 09:29:39 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/fdf.h"

// Free the memory allocated for a table of t_points
void	free_points_tab(t_point **tab)
{
	ft_printf("free_points_tab\n");
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// Free the memory allocated for a table of strings
void	free_str_tab(char **tab)
{
	ft_printf("free_str_tab\n");
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
