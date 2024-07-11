/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:49:46 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:49:24 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	resize(t_fdf *fdf)
{
	int	new_size;

	new_size = img_size(fdf->win.mlx->width, fdf->win.mlx->height);
	fdf->win.img->instances->x = fdf->win.mlx->width - new_size;
	init_view_port(fdf->cam.vport_m, new_size, new_size);
	mlx_resize_image(fdf->win.img, new_size, new_size);
	redraw(fdf);
}

void	object_mov(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_A))
		set_fdct_mov(&fdf->mov_vec.dsp[0], -1, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_D))
		set_fdct_mov(&fdf->mov_vec.dsp[0], 1, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_W))
		set_fdct_mov(&fdf->mov_vec.dsp[1], 1, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_S))
		set_fdct_mov(&fdf->mov_vec.dsp[1], -1, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_Q) && fdf->cam.prj_tp == PERSP)
		set_fdct_mov(&fdf->mov_vec.dsp[2], -1, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_E) && fdf->cam.prj_tp == PERSP)
		set_fdct_mov(&fdf->mov_vec.dsp[2], 1, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_I))
		set_mov(&fdf->mov_vec.ang[0], -1, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_K))
		set_mov(&fdf->mov_vec.ang[0], 1, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_J))
		set_mov(&fdf->mov_vec.ang[1], -1, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_L))
		set_mov(&fdf->mov_vec.ang[1], 1, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_U))
		set_mov(&fdf->mov_vec.ang[2], 1, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_O))
		set_mov(&fdf->mov_vec.ang[2], -1, &fdf->mov_vec);
}

void	object_scale(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_F))
		set_mov(&fdf->mov_vec.scl, -0.01, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_G))
		set_mov(&fdf->mov_vec.scl, 0.01, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_3) && fdf->cam.prj_tp == PART)
		set_part(&fdf->cam.part, -0.01, &fdf->mov_vec);
	if (mlx_is_key_down(fdf->win.mlx, MLX_KEY_4) && fdf->cam.prj_tp == PART)
		set_part(&fdf->cam.part, 0.01, &fdf->mov_vec);
}
