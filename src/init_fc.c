/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:57:37 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 18:56:27 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(t_map *map)
{
	map->info_nb[0] = 0;
	map->info_nb[1] = 0;
	map->info_nb[2] = 0;
	map->info_nb[3] = 1;
	map->array = NULL;
	map->colors = NULL;
}

static void	put_image(t_fdf *fdf, mlx_image_t *img, int x_pos, int y_pos)
{
	if (!img || mlx_image_to_window(fdf->win.mlx, img, x_pos, y_pos) < 0)
	{
		mlx_check(fdf);
	}
}

void	init_window(t_fdf *fdf, char *file)
{
	fdf->win.mlx = mlx_init(WIDTH, HEIGHT, file, true);
	if (!fdf->win.mlx)
	{
		free_map_arrays(fdf);
		error_text("Failed to initialaze mlx.\n");
	}
	fdf->win.img = mlx_new_image(fdf->win.mlx, WIDTH, HEIGHT);
	put_image(fdf, fdf->win.img, 0, 0);
}
