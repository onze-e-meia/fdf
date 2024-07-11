/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:27:10 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 19:48:15 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	vector_copy(point, new_point);
	matrix_vector(cam->proj_m, new_point);
	matrix_vector(cam->vport_m, new_point);
}
