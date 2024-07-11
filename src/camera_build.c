/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:12:15 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 19:45:43 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_volume(t_vol *vol, float aperture);

void	init_view_port(float matrix[4][4], float nx, float ny)
{
	matrix_unit(matrix, 1, 0);
	matrix[0][0] = nx / 2;
	matrix[0][3] = (nx - 1) / 2;
	matrix[1][1] = ny / 2;
	matrix[1][3] = (ny - 1) / 2;
	matrix[2][2] = 0.5;
	matrix[2][3] = 0.5;
}

void	init_camera(t_fdf *fdf)
{
	int		size;

	fdf->cam.aprt = aperture(fdf->map.info_nb);
	fdf->cam.orgn[0] = -fdf->map.obj_cent[0];
	fdf->cam.orgn[1] = -fdf->map.obj_cent[1];
	fdf->cam.orgn[2] = -fdf->map.obj_cent[2] - fdf->cam.aprt;
	fdf->cam.orgn[3] = 1;
	fdf->cam.ang[0] = 0;
	fdf->cam.ang[1] = 0;
	fdf->cam.ang[2] = 0;
	init_volume(&fdf->cam.vol, fdf->cam.aprt);
	size = img_size(fdf->win.mlx->width, fdf->win.mlx->height);
	init_view_port(fdf->cam.vport_m, size, size);
	camera_orient(&fdf->cam);
}

static void	init_volume(t_vol *vol, float aperture)
{
	vol->left = -aperture / 1.5;
	vol->right = aperture / 1.5;
	vol->bottom = aperture / 1.5;
	vol->top = -aperture / 1.5;
	vol->near = aperture / 2 ;
	vol->far = 16 * aperture;
}

void	camera_orient(t_cam *cam)
{
	float	trans[4][4];
	float	rot[4][4];
	float	orient[4][4];
	float	proj[4][4];

	translation(trans, cam->orgn);
	rotation(rot, cam->ang);
	matrix_mult(rot, trans, orient);
	orthographic(proj, cam->vol);
	matrix_mult(proj, orient, cam->proj_m);
}
