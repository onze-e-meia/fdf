/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:17:46 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:49:08 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	error_text(char *str)
{
	if (errno)
	{
		ft_putstr_fd("ERROR: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		perror("Error");
	}
	else
	{
		ft_putstr_fd("ERROR: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	exit(EXIT_FAILURE);
}

void	free_array(void ***array, int line, int column, int elem)
{
	int	j;
	int	i;

	j = 0;
	while (line > j)
	{
		i = 0;
		while (elem > 1 && column > i)
		{
			free(array[j][i]);
			i++;
		}
		free(array[j]);
		j++;
	}
	free(array);
}

void	free_map_arrays(t_fdf *fdf)
{
	if (fdf->map.array)
		free_array((void ***) fdf->map.array,
			fdf->map.info_nb[1], fdf->map.info_nb[0], 4);
	if (fdf->map.colors)
		free_array((void ***) fdf->map.colors,
			fdf->map.info_nb[1], fdf->map.info_nb[0], 1);
	if (fdf->map.colorh)
		free_array((void ***) fdf->map.colorh,
			fdf->map.info_nb[1], fdf->map.info_nb[0], 1);
}

void	mlx_check(t_fdf *fdf)
{
	if (fdf->win.mlx && !fdf->win.img)
	{
		free_map_arrays(fdf);
		mlx_terminate(fdf->win.mlx);
		error_text("Failed to initialaze image.\n");
	}
	if (!fdf->win.menu)
	{
		free_map_arrays(fdf);
		mlx_delete_image(fdf->win.mlx, fdf->win.img);
		mlx_terminate(fdf->win.mlx);
		error_text("Failed to initialaze menu.\n");
	}
}

void	check_close(int file_descriptor)
{
	if (close(file_descriptor) < 0)
		error_text("ERROR: Invalid file to close.\n");
}
