/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:27:10 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:49:02 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	point_clip(float point[3], t_prj_tp prj_tp);

/*
* Aperure is camera's field of view.
* It's aspect (widht x height) and distance from the focal point;
* This is to ensure that the object can freely rotate in the fiel of view.
* Return the bigest axis dimension (x, y, z) of the image.
*/
float	aperture(int info_nb[4])
{
	return (sqrtf(powf(info_nb[0], 2)
			+ powf(info_nb[1], 2)
			+ powf(info_nb[2], 2)));
}

/*
* Return the smallet value between the width and height.
*/
int	img_size(int width, int height)
{
	return ((width >= height) * height + (height > width) * width);
}

void	point_proj(t_cam *cam, float point[4], float new_point[4])
{
	int	clip;

	vector_copy(point, new_point);
	matrix_vector(cam->proj_m, new_point);
	clip = point_clip(new_point, cam->prj_tp);
	if (cam->prj_tp == PERSP || cam->prj_tp == PART)
		vector_mult(new_point, (float)(1 / new_point[3]));
	matrix_vector(cam->vport_m, new_point);
	new_point[3] = clip;
}

/*
* Check for the cliping range of the coordinate Z.
* If the clip coordinate is less than w_clip,
* or greater than w_clip, then the vertex will be discarded.
*/
static int	point_clip(float point[3], t_prj_tp prj_tp)
{
	float	w_clip;
	int		z_clip;

	z_clip = 0;
	if (prj_tp == ORTHO)
		z_clip = ((-1 < point[2]) && (point[2] < 1));
	else if (prj_tp == PERSP || prj_tp == PART)
	{
		w_clip = point[3];
		z_clip = ((-w_clip < point[1]) && (point[1] < w_clip));
	}
	return (z_clip);
}
