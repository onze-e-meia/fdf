/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_build_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:12:15 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:49:00 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
	fdf->cam.prj_tp = ORTHO;
	fdf->cam.part = 0;
	fdf->mov_vec.mov_proj = OBJ;
	size = img_size(fdf->win.mlx->width, fdf->win.mlx->height);
	init_view_port(fdf->cam.vport_m, size, size);
	camera_orient(&fdf->cam);
}

static void	init_volume(t_vol *vol, float aperture)
{
	vol->left = -aperture / 2;
	vol->right = aperture / 2;
	vol->bottom = aperture / 2;
	vol->top = -aperture / 2;
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
	if (cam->prj_tp == ORTHO)
		orthographic(proj, cam->vol);
	else if (cam->prj_tp == PERSP)
		perspective(proj, cam->vol);
	else if (cam->prj_tp == PART)
		partial(proj, cam->vol, cam->part);
	matrix_mult(proj, orient, cam->proj_m);
}

void	rebuild_cam(t_cam *cam, t_mov_vec *mov_vec)
{
	cam->orgn[0] -= mov_vec->dsp[0];
	cam->orgn[1] -= mov_vec->dsp[1];
	if (cam->prj_tp == PERSP || cam->prj_tp == PART)
		cam->orgn[2] += mov_vec->dsp[2];
	cam->ang[0] += mov_vec->ang[0];
	cam->ang[1] += mov_vec->ang[1];
	cam->ang[2] -= mov_vec->ang[2];
}
