/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oprt_rotate_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:30:03 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:49:36 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	rotate_x(float matrix[4][4], float theta)
{
	matrix_unit(matrix, 1, 0);
	matrix[1][1] = cosf(theta * M_PI / 180.0);
	matrix[1][2] = -sinf(theta * M_PI / 180.0);
	matrix[2][1] = sinf(theta * M_PI / 180.0);
	matrix[2][2] = cosf(theta * M_PI / 180.0);
}

void	rotate_y(float matrix[4][4], float theta)
{
	matrix_unit(matrix, 1, 0);
	matrix[0][0] = cosf(theta * M_PI / 180.0);
	matrix[0][2] = sinf(theta * M_PI / 180.0);
	matrix[2][0] = -sinf(theta * M_PI / 180.0);
	matrix[2][2] = cosf(theta * M_PI / 180.0);
}

void	rotate_z(float matrix[4][4], float theta)
{
	matrix_unit(matrix, 1, 0);
	matrix[0][0] = cosf(theta * M_PI / 180.0);
	matrix[0][1] = -sinf(theta * M_PI / 180.0);
	matrix[1][0] = sinf(theta * M_PI / 180.0);
	matrix[1][1] = cosf(theta * M_PI / 180.0);
}

void	rotation(float rot[4][4], float ang[3])
{
	float	rot_x[4][4];
	float	rot_y[4][4];
	float	rot_z[4][4];
	float	temp[4][4];

	rotate_x(rot_x, ang[0]);
	rotate_y(rot_y, ang[1]);
	matrix_mult(rot_y, rot_x, temp);
	rotate_z(rot_z, ang[2]);
	matrix_mult(rot_z, temp, rot);
}
