/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 23:58:41 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 20:19:04 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vrtx	init_vrtx(t_fdf *fdf, float ***batch, int line, int col)
{
	t_vrtx	vertex;

	vertex.point[0] = (int) batch[line][col][0];
	vertex.point[1] = (int) batch[line][col][1];
	vertex.point[2] = (int) batch[line][col][2];
	vertex.point[3] = (int) batch[line][col][3];
	vertex.color.value = fdf->map.colors[line][col];
	return (vertex);
}

float	dist_2d(int p0[4], int p1[4])
{
	return (sqrtf(powf(p1[0] - p0[0], 2) + powf(p1[1] - p0[1], 2)));
}
