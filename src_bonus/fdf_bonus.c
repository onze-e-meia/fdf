/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:36:46 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:49:11 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

float	mov_factor(t_fdf *fdf)
{
	float	trans[4][4];
	float	proj[4][4];
	float	point[4];
	float	proj_p[4];
	float	displace;

	translation(trans, fdf->cam.orgn);
	if (fdf->cam.prj_tp == ORTHO)
		orthographic(proj, fdf->cam.vol);
	else if (fdf->cam.prj_tp == PERSP || fdf->cam.prj_tp == PART)
		perspective(proj, fdf->cam.vol);
	matrix_mult(proj, trans, fdf->cam.proj_m);
	init_vector(0, 0, fdf->map.obj_cent[2], point);
	point_proj(&fdf->cam, point, proj_p);
	displace = -proj_p[0];
	init_vector(1, 1, fdf->map.obj_cent[2], point);
	point_proj(&fdf->cam, point, proj_p);
	displace += proj_p[0];
	return (displace);
}

void	init_mov_vector(t_fdf *fdf)
{
	int	new_size;

	new_size = img_size(fdf->win.mlx->width, fdf->win.mlx->height);
	fdf->mov_vec.dsp[0] = 0;
	fdf->mov_vec.dsp[1] = 0;
	fdf->mov_vec.dsp[2] = 0;
	fdf->mov_vec.dsp[3] = 0;
	fdf->mov_vec.ang[0] = 0;
	fdf->mov_vec.ang[1] = 0;
	fdf->mov_vec.ang[2] = 0;
	fdf->mov_vec.scl = 0;
	fdf->mov_vec.fct = mov_factor(fdf) / 2;
	fdf->mov_vec.redraw = NO;
}

void	redraw(t_fdf *fdf)
{
	camera_orient(&fdf->cam);
	ft_memset(fdf->win.img->pixels, 27,
		fdf->win.img->width * fdf->win.img->height * 4);
	draw_frame(fdf->win.img);
	fdf_draw(fdf);
}

static void	hooks(void *param)
{
	t_fdf		*fdf;

	fdf = (t_fdf *) param;
	init_mov_vector(fdf);
	object_mov(fdf);
	object_scale(fdf);
	if (fdf->mov_vec.redraw == YES && fdf->mov_vec.mov_proj == OBJ)
		fdf_transform(&fdf->map, &fdf->mov_vec);
	if (fdf->mov_vec.redraw == YES && fdf->mov_vec.mov_proj == CAM)
		rebuild_cam(&fdf->cam, &fdf->mov_vec);
	if (fdf->mov_vec.redraw == YES)
		redraw(fdf);
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
	init_colorh(&fdf);
	init_window(&fdf, argv[1]);
	init_camera(&fdf);
	draw_menu(&fdf.win);
	text_menu(&fdf.win);
	redraw(&fdf);
	mlx_key_hook(fdf.win.mlx, basic_keys, &fdf);
	mlx_loop_hook(fdf.win.mlx, hooks, &fdf);
	mlx_loop(fdf.win.mlx);
	mlx_terminate(fdf.win.mlx);
	free_map_arrays(&fdf);
	return (EXIT_SUCCESS);
}
