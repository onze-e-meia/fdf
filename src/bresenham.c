/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:58:08 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 16:40:53 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_ctrl_pts(t_ctrl *ctrl, int p0[4], int p1[4]);
static void	draw_line(t_fdf *fdf, t_vrtx *start, t_vrtx *end, t_ctrl *ctrl);
static void	point_in_vp(t_fdf *fdf, t_vrtx *start, t_vrtx *end, t_ctrl *ctrl);

void	bresenham(t_fdf *fdf, t_vrtx start, t_vrtx end)
{
	t_ctrl	ctrl;

	init_ctrl_pts(&ctrl, start.point, end.point);
	ctrl.dist = (float) 1 / dist_2d(start.point, end.point);
	draw_line(fdf, &start, &end, &ctrl);
}

static void	init_ctrl_pts(t_ctrl *ctrl, int p0[4], int p1[4])
{
	ctrl->dx = abs(p1[0] - p0[0]);
	ctrl->sx = (1 * (p0[0] < p1[0]) - 1 * (p0[0] >= p1[0]));
	ctrl->dy = -abs(p1[1] - p0[1]);
	ctrl->sy = (1 * (p0[1] < p1[1]) - 1 * (p0[1] >= p1[1]));
	ctrl->err = ctrl->dx + ctrl->dy;
	ctrl->dist = 0;
	ctrl->step = 0;
}

static void	draw_line(t_fdf *fdf, t_vrtx *start, t_vrtx *end, t_ctrl *ctrl)
{
	while (YES)
	{
		point_in_vp(fdf, start, end, ctrl);
		if (start->point[0] == end->point[0]
			&& start->point[1] == end->point[1])
			break ;
		ctrl->e2 = 2 * ctrl->err;
		if (ctrl->e2 >= ctrl->dy)
		{
			if (start->point[0] == end->point[0])
				break ;
			ctrl->err += ctrl->dy;
			start->point[0] += ctrl->sx;
		}
		if (ctrl->e2 <= ctrl->dx)
		{
			if (start->point[1] == end->point[1])
				break ;
			ctrl->err += ctrl->dx;
			start->point[1] += ctrl->sy;
		}
	}
}

static void	point_in_vp(t_fdf *fdf, t_vrtx *start, t_vrtx *end, t_ctrl *ctrl)
{
	t_color		color;
	uint32_t	un_start0;
	uint32_t	un_start1;

	un_start0 = (uint32_t) start->point[0];
	un_start1 = (uint32_t) start->point[1];
	if ((3 <= un_start0 && un_start0 < fdf->win.img->width - 3)
		&& (3 <= un_start1 && un_start1 < fdf->win.img->height - 3))
	{
		color = intrplt_color(start->color, end->color, ctrl->step);
		ctrl->step += (ctrl->step <= 1) * ctrl->dist + (ctrl->step > 1) * 1;
		mlx_put_pixel(fdf->win.img,
			un_start0, un_start1, color.value);
	}
}
