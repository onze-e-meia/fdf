/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:37:42 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 18:05:11 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	mod_cam(mlx_key_data_t keydata, t_fdf *fdf);

void	text_menu(t_window *win)
{
	int	line;

	line = 0;
	mlx_put_string(win->mlx, "======= MENU =======", 10, line += 10);
	mlx_put_string(win->mlx, "---- Translation ---", 10, line += 40);
	mlx_put_string(win->mlx, "      Up:  W        ", 10, line += 20);
	mlx_put_string(win->mlx, " Back: Q    Front: E", 10, line += 20);
	mlx_put_string(win->mlx, " Left: A    Right: D", 10, line += 20);
	mlx_put_string(win->mlx, "    Down:  S        ", 10, line += 20);
	mlx_put_string(win->mlx, "----- Rotation -----", 10, line += 40);
	mlx_put_string(win->mlx, "      Up:  I        ", 10, line += 20);
	mlx_put_string(win->mlx, " Z_Lt: Q    Z_Rht  E", 10, line += 20);
	mlx_put_string(win->mlx, " Left: J    Right  L", 10, line += 20);
	mlx_put_string(win->mlx, "    Down:  K        ", 10, line += 20);
	mlx_put_string(win->mlx, "------- Scale ------", 10, line += 40);
	mlx_put_string(win->mlx, "  Down: F    Up: G  ", 10, line += 20);
	mlx_put_string(win->mlx, "------- Other ------", 10, line += 40);
	mlx_put_string(win->mlx, " Close: ESC         ", 10, line += 20);
	mlx_put_string(win->mlx, " Orthographic : 0   ", 10, line += 20);
	mlx_put_string(win->mlx, " Perspective :  1   ", 10, line += 20);
	mlx_put_string(win->mlx, " Part: 2 (dn:3 up:4)", 10, line += 20);
	mlx_put_string(win->mlx, " Object Move:  X     ", 10, line += 20);
	mlx_put_string(win->mlx, " Camera Move:  C     ", 10, line += 20);
	mlx_put_string(win->mlx, " Color change: Z     ", 10, line += 20);
}

void	basic_keys(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fdf->win.mlx);
	mod_cam(keydata, fdf);
	if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
		fdf->mov_vec.mov_proj = OBJ;
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		fdf->mov_vec.mov_proj = CAM;
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		resize(fdf);
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
	{
		fdf->map.c = (fdf->map.c == 0) * 1;
		ft_memset(fdf->win.img->pixels, 27,
			fdf->win.img->width * fdf->win.img->height * 4);
		color_palete(&fdf->map, fdf->map.c);
		redraw(fdf);
	}
}

static void	mod_cam(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_0 && keydata.action == MLX_PRESS)
	{
		fdf->cam.prj_tp = ORTHO;
		redraw(fdf);
	}
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		fdf->cam.prj_tp = PERSP;
		redraw(fdf);
	}
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
	{
		fdf->cam.prj_tp = PART;
		redraw(fdf);
	}
}

void	draw_frame(mlx_image_t *img)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < img->width)
	{
		j = 0;
		while (j < 3)
		{
			mlx_put_pixel(img, i, j, FRAME_C);
			mlx_put_pixel(img, i, img->height - 1 - j++, FRAME_C);
		}
		i++;
	}
	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < 3)
		{
			mlx_put_pixel(img, j, i, FRAME_C);
			mlx_put_pixel(img, img->width -1 - j++, i, FRAME_C);
		}
		i++;
	}
}

void	draw_menu(t_window *win)
{
	ft_memset(win->menu->pixels, MENU_C,
		win->menu->width * win->menu->height * 4);
	text_menu(win);
}
