/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:41:11 by chdonnat          #+#    #+#             */
/*   Updated: 2025/01/29 08:54:37 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to convert a string to a long integer
long	ft_atoi_long(const char *nptr)
{
	int		i;
	int		sign;
	long	result;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

// Function to compare 2 floats and return 1 or -1
int	compare(float n1, float n2)
{
	if (n1 < n2)
		return (1);
	return (-1);
}

// Function to check if the input is a number
int	is_number(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '\0')
		return (1);
	if (str[i] == 43 || str[i] == 45)
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	return (1);
}

int	check_fdf_extension(const char *filename)
{
	const char	*ext;
	const char	*file_ext;
	size_t		len_filename;
	size_t		len_ext;

	ext = ".fdf";
	len_filename = ft_strlen(filename);
	len_ext = ft_strlen(ext);
	if (len_filename < len_ext)
		return (0);
	file_ext = filename + len_filename - len_ext;
	if (ft_strncmp(file_ext, ext, 4) == 0)
		return (1);
	else
		return (0);
}

// Function to allocate memory to fdf
t_fdf	*malloc_fdf(void)
{
	t_fdf	*fdf;

	fdf = NULL;
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	return (fdf);
}
