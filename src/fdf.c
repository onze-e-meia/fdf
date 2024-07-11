/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:36:46 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 19:49:23 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_mov_vector(t_fdf *fdf)
{
	fdf->mov_vec.dsp[0] = 0;
	fdf->mov_vec.dsp[1] = 0;
	fdf->mov_vec.dsp[2] = 0;
	fdf->mov_vec.dsp[3] = 0;
	fdf->mov_vec.ang[0] = -20;
	fdf->mov_vec.ang[1] = -20;
	fdf->mov_vec.ang[2] = -45;
}

void	redraw(t_fdf *fdf)
{
	ft_memset(fdf->win.img->pixels, 27,
		fdf->win.img->width * fdf->win.img->height * 4);
	fdf_draw(fdf);
}

void	basic_keys(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fdf->win.mlx);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc < 2 || argv[1] == (void *)0)
		error_text("No <map_name>.fdf to read.\n");
	else if (argc > 2)
		error_text("To many arguments.\n");
	init_map(&fdf.map);
	fdf_read(&fdf.map, argv[1]);
	init_window(&fdf, argv[1]);
	init_camera(&fdf);
	init_mov_vector(&fdf);
	fdf_transform(&fdf.map, &fdf.mov_vec);
	redraw(&fdf);
	mlx_key_hook(fdf.win.mlx, basic_keys, &fdf);
	mlx_loop(fdf.win.mlx);
	mlx_terminate(fdf.win.mlx);
	free_map_arrays(&fdf);
	return (EXIT_SUCCESS);
}
